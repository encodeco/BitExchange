#pragma once

#include "./RedisTask.h"

#include "OrderBook/OrderBook.h"

#include "./utils/BETime.h"

#include "RedisTask.h"
#include "MongoTask.h"
#include <mutex>


#include "./protobuf/Service.pb.h"

using be::protobuf::Service;

class ServerStartModule {
public:
	static int run(int argc, char* argv[]) {


		std::mutex mu;
		Service::QuoteList quotes;

		// Creating REDIS Task
		RedisTask redis_task;

		//Creating a thread to execute REDIS task
		std::thread redis_th([&]()
		{
			redis_task.run(quotes, mu);
		});

		// main thread
		std::unique_ptr <OrderBook> orderbook = std::make_unique<OrderBook>();

		int count_of_processed = 0;
		while (true)
		{
			BETime timestamp;
			timestamp.start();

			//Quote quote;

			std::unique_lock < std::mutex > locker(mu);

			auto qu = quotes.mutable_quotes();

			bool b_exist = false;
			be::protobuf::Service::Quote searched_quote;

			if (!qu->empty()) {
				b_exist = true;
				auto last_item = qu->rbegin();
				searched_quote.CopyFrom((*last_item));

				 
				auto temp = searched_quote.order_type();

				qu->RemoveLast();
			}

			locker.unlock();

			if(b_exist)
			{
				// end lock
				std::pair<std::vector<TransactionRecord>, be::protobuf::Service::Quote> ret = orderbook->process_order(searched_quote, false, false);

				std::string ostr = orderbook->text();
				std::cout << ostr;
				std::cout << ++count_of_processed << " " << std::endl;

				std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			}
			timestamp.stop();

			//cout << timestamp.diff().count() << std::endl;
		}

		std::cout << "Asking Task to Stop" << std::endl;

		// Stop the Task
		redis_task.stop();
		//Waiting for thread to join
		redis_th.join();


		std::cout << "Thread Joined" << std::endl;
		std::cout << "Exiting Main Function" << std::endl;

		return 0;
	}
};