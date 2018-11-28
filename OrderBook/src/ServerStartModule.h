#pragma once

#include "./RedisTask.h"

#include "OrderBook/OrderBook.h"

#include "./utils/BETime.h"

#include "./test/TestStartModule.h"

class ServerStartModule {
public:
	static int run(int argc, char* argv[]) {
		// Creating our Task
		RedisTask redis_task;

		//Creating a thread to execute our task
		std::thread th([&]()
		{
			redis_task.run();
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
				//orderbook->print();

				std::cout << ++count_of_processed << " " << std::endl;
			}
			timestamp.stop();

			//cout << timestamp.diff().count() << std::endl;
		}

		std::cout << "Asking Task to Stop" << std::endl;
		// Stop the Task
		redis_task.stop();

		//Waiting for thread to join
		th.join();
		std::cout << "Thread Joined" << std::endl;
		std::cout << "Exiting Main Function" << std::endl;

		return 0;

		return 0;
	}
};