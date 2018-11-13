#include "JsonTestData.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

#include "OrderBook/common.h"
#include "OrderBook/OrderBook.h"
#include "OrderBook/Quote.h"

#include "json11/json11.hpp"

using namespace std;

#define DATAFILE_JSON_0 "./resources/testdata_0.json"
#define DATAFILE_JSON_1 "./resources/testdata_1.json"

JsonTestData::JsonTestData(int argc, char* argv[]) : TestData(argc, argv)
{
	
}


JsonTestData::~JsonTestData()
{
}

int JsonTestData::DoTestProcess()
{

	// Read Quotes from csv;
	std::vector< Quote > quotes0;
	std::vector< Quote > quotes1;

	//JsonTestData test;

	JsonTestData::read_quote_from_json(DATAFILE_JSON_0, quotes0);
	JsonTestData::read_quote_from_json(DATAFILE_JSON_1, quotes1);

	////read_quote_from_csv(DATAFILE_CSV, quotes);

	////cout << quotes.size() << " quote(s) created" << endl;

	std::unique_ptr <OrderBook> orderbook = std::make_unique<OrderBook>();

	int cnt = 0;
	for (auto quote : quotes0) {
		cout << "############# " << ++cnt << "th" << endl;
		std::pair<std::vector<TransactionRecord>, Quote> ret = orderbook->process_order(quote, false, false);
		orderbook->print();
		}

	for (auto quote : quotes1) {
		cout << "############# " << ++cnt << "th" << endl;
		std::pair<std::vector<TransactionRecord>, Quote> ret = orderbook->process_order(quote, false, false);
		for (auto a_trade : ret.first) {
			a_trade.print();
		}
		orderbook->print();
	}
	return 0;
}

int JsonTestData::read_quote_from_json(const char *file_in, std::vector <Quote> &quotes )
{
	string jsondata = "";
	ifstream ifs(file_in);
	string buf;
	while (ifs && getline(ifs, buf))
		jsondata += buf;

	string err;
	auto json = json11::Json::parse(jsondata, err);

	for (auto item : json.array_items()) {
		std::vector <std::string>  values;
		values.push_back(item["type"].string_value());
		values.push_back(item["side"].string_value());
		values.push_back(std::to_string(item["quantity"].int_value()));
		values.push_back(std::to_string(item["price"].int_value()));
		values.push_back(std::to_string(item["trade_id"].int_value()));
		values.push_back(std::to_string(0));

		Quote quote(values);
		quotes.push_back(quote);
	}
	return 0;
}

