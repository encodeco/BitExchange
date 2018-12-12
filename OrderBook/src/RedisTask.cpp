#include "RedisTask.h"

#include <iostream>
#include <string>
#include <map>
#include <mutex>
#include <boost/algorithm/string/case_conv.hpp>
#include "OrderBook/common.h"
#include "OrderBook/OrderBook.h"

#include "utils/parse.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6379

#define GET_LIST_MAX 3 // 0 base!S

#include "utils/redispp.h"

RedisTask::RedisTask()
{

}
RedisTask::~RedisTask()
{

}
void RedisTask::run()
{
}
void RedisTask::run(be::protobuf::Service::QuoteList &quotes, std::mutex &mu)
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
				time_t timestamp;
				time(&timestamp);

				std::string delimeter = "-";
				std::vector <std::string> parsed;
				parse(delimeter, redis.resp->str, parsed);

				enum { ORDER_ID, TYPE, SIDE, QUANTITY, PRICE, TRADER_ID };

				std::unique_lock < std::mutex > locker(mu);

				auto new_quote = quotes.add_quotes();

				new_quote->set_order_type( boost::algorithm::to_upper_copy(parsed[TYPE]) );
				new_quote->set_order_side( boost::algorithm::to_upper_copy(parsed[SIDE]) );

				auto new_order_in_quote = new_quote->mutable_order();
				new_order_in_quote->set_quantity( std::stoi( parsed[QUANTITY] ) );
				new_order_in_quote->set_price(std::stoi(parsed[PRICE]));

				new_order_in_quote->set_trader_id(std::stoi(parsed[TRADER_ID]));
				new_order_in_quote->set_order_id(std::stoi(parsed[ORDER_ID]));
				new_order_in_quote->set_timestamp(timestamp);

				locker.unlock();

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
