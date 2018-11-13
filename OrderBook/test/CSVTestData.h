#pragma once

#include "TestData.h"

#include <vector>
#include "OrderBook/Quote.h"

class CSVTestData : public TestData
{
public:
	CSVTestData(int argc, char* argv[]);
	CSVTestData() { ; }
	~CSVTestData();

public:
	int DoTestProcess();
	int read_quote_from_csv(const char *file_in, std::vector <Quote> &quotes);
};

