#pragma once

#include "TestData.h"

#include <vector>
#include "OrderBook/Quote.h"

#include "redispp/redispp.h"

class RedisTestData : public TestData
{
public:
	RedisTestData(int argc, char* argv[]);
	RedisTestData() { ; }
	~RedisTestData();

public:
	redispp redis;

public:
	int DoTestProcess();
	int read_quote_from_redis(std::vector <Quote> &quotes);
	bool read_quote_from_redis_pop(std::vector <Quote> &quotes);
};

