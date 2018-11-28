#include "RedisTask.h"

#include <iostream>
#include <string>
#include <map>
#include <mutex>

#include "OrderBook/common.h"
#include "OrderBook/OrderBook.h"
#include "OrderBook/Quote.h"
#include "utils/parse.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6379

#define GET_LIST_MAX 3 // 0 base!S

#include "utils/redispp.h"

void RedisTask::run()
{
	redispp redis;
	redis.connect(SERVER_IP, SERVER_PORT);

	std::cout << "start wait for queue" << std::endl;

	std::unique_ptr <OrderBook> orderbook = std::make_unique<OrderBook>();
	while (stopRequested() == false)
	{
		try {
			redis.redisCommand("LPOP order");

			if (redis.resp->str && strlen(redis.resp->str))
			{
				std::string delimeter = "-";
				std::vector <std::string> parsed;
				parse(delimeter, redis.resp->str, parsed);

				std::map <std::string, std::string> mapitem;
				mapitem["oid"] = parsed[0];
				mapitem["type"] = parsed[1];
				mapitem["side"] = parsed[2];
				mapitem["quantity"] = parsed[3];
				mapitem["price"] = parsed[4];
				mapitem["tid"] = parsed[5];

				Quote quote(mapitem);
				quote.set_current_timestamp();

				// thread safe
				safe_insert(quote);

				//std::cout << quote.to_text() << std::endl;

				redis.free_reply_object();
			}
			else 
			{
				redis.free_reply_object();
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		catch (int e) {
			std::cout << "redis read error " << e;
		}
	}
}


// Function to be executed by thread function
void RedisTask::safe_insert(Quote quote)
{
	std::unique_lock < std::mutex > locker(mu);

	quotes.push_front(quote);

	locker.unlock();

	cond.notify_one();
}

// Function to be executed by thread function
bool RedisTask::safe_pop(Quote &quote)
{
	bool exist = false;
	std::unique_lock < std::mutex > locker(mu);

	if (!quotes.empty()) {
		quote = quotes.front();
		quotes.pop_front();
		exist = true;
	}
	locker.unlock();

	return exist;
}

void RedisTask::run2()
{
	redispp redis;
	redis.connect(SERVER_IP, SERVER_PORT);


	std::cout << "start wait for queue" << std::endl;

	std::unique_ptr <OrderBook> orderbook = std::make_unique<OrderBook>();
	while (stopRequested() == false)
	{
		redis.redisCommand( (std::string("lrange order 0 ") + std::to_string(GET_LIST_MAX) ).c_str() );

		int deleted_count = 0;
		if (redis.resp->type == REDIS_REPLY_ARRAY) {
			for ( deleted_count = 0; deleted_count < redis.resp->elements; deleted_count++) {

				std::string delimeter = "-";
				std::vector <std::string> parsed;
				parse(delimeter, redis.resp->element[deleted_count]->str, parsed);

				std::map <std::string, std::string> mapitem;
				mapitem["oid"] = parsed[0];
				mapitem["type"] = parsed[1];
				mapitem["side"] = parsed[2];
				mapitem["quantity"] = parsed[3];
				mapitem["price"] = parsed[4];
				mapitem["tid"] = parsed[5];

				Quote quote(mapitem);
				quote.set_current_timestamp();

				// thread safe
				safe_insert(quote);

				std::cout << quote.to_text() << std::endl;
			}
		}
		redis.free_reply_object();

		if (deleted_count != 0) {
			redis.redisCommand((std::string("ltrim order 0 ") + std::to_string((deleted_count + 1)*-1)).c_str());
		}
		redis.free_reply_object();

		//// process order book
		//int cnt = 0;
		//for (auto quote : quotes) {
		//	std::cout << "############# " << ++cnt << "th" << std::endl;
		//	std::pair<std::vector<TransactionRecord>, Quote> ret = orderbook->process_order(quote, false, false);
		//	orderbook->print();
		//}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}





	//std::cout << "Task Start" << std::endl;

	//// Check if thread is requested to stop ?
	//while (stopRequested() == false)
	//{
	//	std::cout << "Doing Some Work" << std::endl;
	//	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	//}
	//std::cout << "Task End" << std::endl;
}






/*

#include "../utils/redispp.h"
#include "../utils/parse.h"

server::server()
{
}


server::~server()
{

}


//TC_TYPE, TC_SIDE, TC_QUANTITY, TC_PRICE, TC_ID, TC_TIMESTAMP };
bool read_quote_from_redis_pop(redispp& redis, std::vector <Quote> &quotes)
{
	try {
		redis.redisCommand("LPOP order");

		if (redis.resp->str && strlen(redis.resp->str)) {

			//std::cout << redis.resp->str;
			std::string delimeter = "-";
			std::vector <std::string> parsed;
			parse(delimeter, redis.resp->str, parsed);

			std::map <std::string, std::string> mapitem;
			mapitem["oid"] = parsed[0];
			mapitem["type"] = parsed[1];
			mapitem["side"] = parsed[2];
			mapitem["quantity"] = parsed[3];
			mapitem["price"] = parsed[4];
			mapitem["tid"] = parsed[5];

			//Quote quote(mapitem);
			//quote.set_current_timestamp();
			//quotes.push_back(quote);

			//redis.free_reply_object();

			return true;
		}


		redis.free_reply_object();
		return false;
	}
	catch (int e) {
		std::cout << "redis read error " << e;
	}

	return false;
}

void threadFunction(std::future<void> futureObj, server* svr)
{
	std::cout << "Thread Start" << std::endl;

	redispp redis;
	redis.connect("127.0.0.1", 6379);


	std::cout << "Redis connected" << std::endl;

	while (futureObj.wait_for(std::chrono::milliseconds(10)) == std::future_status::timeout)
	{
		std::cout << "Doing Some Work" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		std::vector <Quote> quotes;
		read_quote_from_redis_pop(redis, quotes);

		for (auto aquote : quotes) {
			svr->queue.push(aquote);
		}

	}
	std::cout << "Thread End" << std::endl;
}

bool server::start()
{
	// Create a std::promise object
	std::promise<void> exitSignal;

	//Fetch std::future object associated with promise
	std::future<void> futureObj = exitSignal.get_future();

	// Starting Thread & move the future object in lambda function by reference
	std::thread th(&threadFunction, std::move(futureObj), this);

	int c;
	do {
		c = getchar();
		putchar(c);
	} while (c != '.');


	std::cout << "Asking Thread to Stop" << std::endl;

	//Set the value in promise
	exitSignal.set_value();

	//Wait for thread to join
	th.join();

	std::cout << "Exiting Main Function" << std::endl;
	return 0;
}*/
/*

	int c;
	do {
		c = getchar();
		putchar(c);
	} while (c != '.');

*/


