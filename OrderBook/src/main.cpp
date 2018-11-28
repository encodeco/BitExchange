#include <iostream>

#include "../test/CSVTestData.h"
#include "../test/JsonTestData.h"
#include "../test/RedisTestData.h"
#include "../test/JsonToRedisTestData.h"

#include "./RedisTask.h"

#include "OrderBook/OrderBook.h"

#include "./utils/BETime.h"

using namespace std;

enum TEST_CASE {TC_NONE, TC_JSON, TC_CSV, TC_REDIS, TC_JSON_TO_REDIS };

int main(int argc, char* argv[])
{
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

			cout << ++count_of_processed << " " <<   std::endl;
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

}
int main2(int argc, char* argv[])
{
	TestData *test_data = nullptr;

	//int test_kind = TC_JSON_TO_REDIS;
	int test_kind = TC_JSON_TO_REDIS;

	switch (test_kind) {
	case TC_JSON:
		test_data = new JsonTestData(argc, argv);
		break;
	case TC_CSV:
		test_data = new CSVTestData(argc, argv);
		break;
	case TC_REDIS:
		test_data = new RedisTestData(argc, argv);
		break;
	case TC_JSON_TO_REDIS:
		test_data = new JsonToRedisTestData(argc, argv);
		break;

	}

	if (test_data) {

		test_data->DoTestProcess();

		delete test_data;
		test_data = nullptr;
	}
	return 0;
}







