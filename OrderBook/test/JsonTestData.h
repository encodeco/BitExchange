#pragma once

#include "TestData.h"

#include <vector>
#include "OrderBook/Quote.h"

class JsonTestData : public TestData
{
public:
	JsonTestData(int argc, char* argv[]);
	JsonTestData() {;}
	~JsonTestData();

public:
	int DoTestProcess();
	int read_quote_from_json(const char *file_in, std::vector <Quote> &quotes);
};

