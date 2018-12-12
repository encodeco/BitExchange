#include "JsonTestData.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include  <boost/algorithm/string/case_conv.hpp>

#include "OrderBook/common.h"
#include "OrderBook/OrderBook.h"

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
	std::vector< be::protobuf::Service::Quote > quotes0;
	std::vector< be::protobuf::Service::Quote > quotes1;

	//JsonTestData test;

	JsonTestData::read_quote_from_json(DATAFILE_JSON_0, quotes0);
	JsonTestData::read_quote_from_json(DATAFILE_JSON_1, quotes1);

	////read_quote_from_csv(DATAFILE_CSV, quotes);

	////cout << quotes.size() << " quote(s) created" << endl;

	std::unique_ptr <OrderBook> orderbook = std::make_unique<OrderBook>();

	int cnt = 0;
	for (auto quote : quotes0) {
		cout << "############# " << ++cnt << "th" << endl;
		std::pair<std::vector<TransactionRecord>, be::protobuf::Service::Quote> ret = orderbook->process_order(quote, false, false);
		orderbook->print();
		}

	for (auto quote : quotes1) {
		cout << "############# " << ++cnt << "th" << endl;
		std::pair<std::vector<TransactionRecord>, be::protobuf::Service::Quote> ret = orderbook->process_order(quote, false, false);
		for (auto a_trade : ret.first) {
			a_trade.print();
		}
		orderbook->print();
	}
	return 0;
}

int JsonTestData::read_quote_from_json(const char *file_in, std::vector <be::protobuf::Service::Quote> &quotes )
{
	string jsondata = "";
	ifstream ifs(file_in);
	string buf;
	while (ifs && getline(ifs, buf))
		jsondata += buf;

	string err;
	auto json = json11::Json::parse(jsondata, err);

	for (auto item : json.array_items()) {

		be::protobuf::Service::Quote quote;
		quote.set_order_type(boost::algorithm::to_upper_copy(item["type"].string_value()));
		quote.set_order_side(boost::algorithm::to_upper_copy(item["side"].string_value()));
		quote.mutable_order()->set_quantity(item["quantity"].int_value());
		quote.mutable_order()->set_price(item["price"].int_value());
		quote.mutable_order()->set_trader_id(item["trade_id"].int_value());
		quotes.push_back(quote);
	}
	return 0;
}

