#include "JsonToRedisTestData.h"
#include "JsonTestData.h"

#include <boost/format.hpp>
#include <iostream>
#include<ctime>

#define DATAFILE_JSON_0 "./resources/testdata_0.json"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6379

using namespace std;

JsonToRedisTestData::JsonToRedisTestData(int argc, char* argv[]) : TestData(argc, argv)
{
	redis.connect(SERVER_IP, SERVER_PORT);
}


JsonToRedisTestData::~JsonToRedisTestData()
{
}

int JsonToRedisTestData::DoTestProcess()
{
	std::vector< Quote > quotes;

	JsonTestData json_test_data;

	json_test_data.read_quote_from_json(DATAFILE_JSON_0, quotes);


	write_quote_to_redis(quotes, 1);

	return 0;
}

/*
HMSET order_id:1 type:limit side:bid quantity:6 price:102 trade_id:109

	"type": "limit",
	"side": "bid",
	"quantity": 6,
	"price": 102,
	"trade_id": 109
*/

// return last order-id
int JsonToRedisTestData::write_quote_to_redis(std::vector <Quote> &quotes, int start_order_id )
{
	int order_idx = start_order_id;
	try {
		for (auto quote : quotes) {

			order_idx = (!start_order_id) ? quote.order_id : order_idx;
			quote.set_current_timestamp();

			string command_string = quote.redis_set_list_string(order_idx, 0);

			redis.redisCommand(command_string.c_str());
			order_idx++;
		}
		redis.free_reply_object();

	}
	catch (int e) {
		std::cout << "redis write error " << e;
	}
	return order_idx;
}