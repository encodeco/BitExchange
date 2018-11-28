#pragma once

#include "TestData.h"
#include <vector>
#include "OrderBook/Quote.h"

#include "utils/redispp.h"

class JsonToRedisTestData : public TestData
{
public:
	JsonToRedisTestData(int argc, char* argv[]);
	JsonToRedisTestData() { ; }
	~JsonToRedisTestData();

public:
	redispp redis;


public:
	int DoTestProcess();
	int write_quote_to_redis(std::vector <Quote> &quotes, int start_order_id = 0);
	//int read_quote_from_json(const char *file_in, std::vector <Quote> &quotes);
};

