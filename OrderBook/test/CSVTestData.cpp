#include "CSVTestData.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

#include "OrderBook/common.h"
#include "OrderBook/OrderBook.h"
#include "OrderBook/Quote.h"

#define DATAFILE_CSV "./resources/testdata_0.csv"

using namespace std;

CSVTestData::CSVTestData(int argc, char* argv[]) : TestData(argc, argv)
{
}


CSVTestData::~CSVTestData()
{
}

int CSVTestData::DoTestProcess()
{
	// Read Quotes from csv;
	std::vector< Quote > quotes;
	read_quote_from_csv(DATAFILE_CSV, quotes);


	////read_quote_from_csv(DATAFILE_CSV, quotes);

	////cout << quotes.size() << " quote(s) created" << endl;

	std::unique_ptr <OrderBook> orderbook = std::make_unique<OrderBook>();

	int cnt = 0;
	for (auto quote : quotes) {
		cout << "############# " << ++cnt << "th" << endl;
		std::pair<std::vector<TransactionRecord>, Quote> ret = orderbook->process_order(quote, false, false);
		orderbook->print();
	}


	return 0;
}


int CSVTestData::read_quote_from_csv(const char *file_in, std::vector <Quote> &quotes)
{
	std::ifstream infile(file_in);

	std::vector < std::vector<std::string> > lines;
	std::string line;

	// read all text to memory
	while (std::getline(infile, line))
	{
		std::string delimiter = ",";
		std::vector <std::string> columns;

		size_t pos = 0;
		std::string token;
		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);
			columns.push_back(token);
			line.erase(0, pos + delimiter.length());
		}
		token = line.substr(0, pos);
		columns.push_back(token);


		lines.push_back(columns);
	}

	for (auto columns : lines) {
		Quote quote(columns);
		quotes.push_back(quote);
	}
	return 0;
}