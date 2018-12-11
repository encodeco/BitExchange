#pragma once

#include "../test/CSVTestData.h"
#include "../test/JsonTestData.h"
#include "../test/RedisTestData.h"
#include "../test/JsonToRedisTestData.h"


#include "OrderBook/OrderBook.h"

enum TEST_CASE { TC_NONE, TC_JSON, TC_CSV, TC_REDIS, TC_JSON_TO_REDIS };

class TestStartModule {

public:
	static int run(int argc, char* argv[])
	{
		TestData *test_data = nullptr;

		//int test_kind = TC_JSON_TO_REDIS;
		int test_kind = TC_JSON;

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
};
