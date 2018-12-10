#pragma once

#include "./RedisTask.h"

#include "OrderBook/OrderBook.h"

#include "./utils/BETime.h"
//#include "./test/TestStartModule.h"

#include "RedisTask.h"
#include "MongoTask.h"

class ServerStartModule {
public:
	static int run(int argc, char* argv[]) {
		// Creating REDIS Task
		RedisTask redis_task;

		//Creating a thread to execute REDIS task
		std::thread redis_th([&]()
		{
			redis_task.run();
		});

		// Creating MONOGO Task
		MongoTask mongo_task;

		//Creating a thread to execute MONOGO task
		std::thread mongo_th([&]()
		{
			mongo_task.run();
		});





		// main thread
		std::unique_ptr <OrderBook> orderbook = std::make_unique<OrderBook>();

		int count_of_processed = 0;
		while (true)
		{
			BETime timestamp;
			timestamp.start();
			Quote quote;
			if (redis_task.safe_pop(quote)) {

				std::pair<std::vector<TransactionRecord>, Quote> ret = orderbook->process_order(quote, false, false);

				auto bidask = orderbook->builder();


				std::string ostr = orderbook->text();
				std::cout << ostr;
				std::cout << ++count_of_processed << " " << std::endl;

				std::this_thread::sleep_for(std::chrono::milliseconds(1000));

				mongo_task.safe_insert(bidask);
				//mongo_task.safe_insert(bidask);
			}
			timestamp.stop();

			//cout << timestamp.diff().count() << std::endl;
		}

		std::cout << "Asking Task to Stop" << std::endl;

		// Stop the Task
		redis_task.stop();
		//Waiting for thread to join
		redis_th.join();

		// Stop the Task
		mongo_task.stop();
		//Waiting for thread to join
		mongo_th.join();

		std::cout << "Thread Joined" << std::endl;
		std::cout << "Exiting Main Function" << std::endl;

		return 0;

		return 0;
	}
};