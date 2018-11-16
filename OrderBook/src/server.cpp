#include "server.h"
#include <thread>
#include <iostream>
#include <chrono>

#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

#include "../utils/redispp/redispp.h"
#include "../utils/parse/parse.h"

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

	while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
	{
		std::cout << "Doing Some Work" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		
		svr->queue.push(Quote());



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
}
/*

	int c;
	do {
		c = getchar();
		putchar(c);
	} while (c != '.');

*/