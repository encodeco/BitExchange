﻿#include "RedisTestData.h"
#include <iostream>
#include <string>
#include <map>

#include "OrderBook/common.h"
#include "OrderBook/OrderBook.h"
#include "OrderBook/Quote.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6379

RedisTestData::RedisTestData(int argc, char* argv[]) : TestData(argc, argv)
{
	redis.connect(SERVER_IP, SERVER_PORT);
}

RedisTestData::~RedisTestData()
{
}

int RedisTestData::DoTestProcess()
{
	// Read Quotes from csv;
	std::vector< Quote > quotes;
	read_quote_from_redis(quotes);

	std::unique_ptr <OrderBook> orderbook = std::make_unique<OrderBook>();

	int cnt = 0;
	for (auto quote : quotes) {
		std::cout << "############# " << ++cnt << "th" << std::endl;
		std::pair<std::vector<TransactionRecord>, Quote> ret = orderbook->process_order(quote, false, false);
		orderbook->print();
	}


	return 0;
}
/*
HMSET order_id:2 type limit side bid quantity 6 price 102 trade_id 109
*/


int RedisTestData::read_quote_from_redis(std::vector <Quote> &quotes)
{
	try {

		redis.redisCommand("KEYS order_id*");

		std::vector < int > order_ids;
		for (size_t i = 0; i < redis.resp->elements; i++ ) {
			
			std::string retvalue = redis.resp->element[i]->str;
			retvalue = retvalue.substr(strlen("order_id:"), retvalue.length()-1);

			order_ids.push_back(std::stoi(retvalue));
		}

		redis.free_reply_object();

		for (auto i : order_ids) {

			redis.redisCommand("HGETALL order_id:%d", i);

			std::map < std::string, std::string > ret_map;
			for (size_t j = 0; j < redis.resp->elements; j=j+2 ) {
				std::string key = redis.resp->element[j]->str;
				std::string val = redis.resp->element[j+1]->str;

				ret_map[key] = val;
			}

			//enum TICK_COLUMN { TC_TYPE, TC_SIDE, TC_QUANTITY, TC_PRICE, TC_ID, TC_TIMESTAMP };
			Quote quote;
			quote.order_id		= i;
			quote.order_side	= toupper(ret_map["side"][0]);
			quote.order_type	= toupper(ret_map["type"][0]);
			quote.price			= std::stoi(ret_map["price"]);
			quote.quantity		= std::stoi(ret_map["quantity"]);
			//quote.timestamp		= std::stoi(ret_map["timestamp"]);
			quote.trade_id		= std::stoi(ret_map["trade_id"]);
			quotes.push_back(quote);

			redis.free_reply_object();
		}

		//printf("%d : %s\n", loop, redis.resp->str);

	}
	catch (int e) {
		std::cout << "redis read error " << e;
	}

	return 0;
}
