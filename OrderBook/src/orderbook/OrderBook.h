#pragma once

#include <deque>
#include <vector>
#include <iostream>

#include "./protobuf/Service.pb.h"

class OrderTree;
class OrderList;

struct TransactionRecord {
	time_t				timestamp;
	unsigned __int64	price;
	unsigned int		quantity;
	time_t				time;

	struct Party1_ {
		unsigned int counter_party;
		char side;
		unsigned __int64 order_id;
		unsigned int book_quantity;
	}party1;

	struct Party12 {
		unsigned int trade_id;
		char side;
	}party2;

	void print() {
		std::cout << party2.trade_id << " " <<  party1.side << std::endl;
	}
};

class OrderBook
{
private:
	std::deque < TransactionRecord >	tape;

	OrderTree							*bids;
	OrderTree							*asks;

	long								time_stamp;
	unsigned int						tick_size;
	time_t								time;
	unsigned int						next_order_id;

public:
	OrderBook();
	~OrderBook();

public:

	std::pair<unsigned int, std::vector<TransactionRecord>>  process_order_list(be::protobuf::Service::Quote &quote, char side, std::shared_ptr<OrderList> order_list, unsigned int quantity_still_to_trade, bool verbose);
	std::pair<std::vector<TransactionRecord>, be::protobuf::Service::Quote> process_order(be::protobuf::Service::Quote &quote, bool from_data, bool verbose);
	void update_time();

	std::vector<TransactionRecord> process_market_order(be::protobuf::Service::Quote &quote, bool verbose);
	std::pair<std::vector<TransactionRecord>, be::protobuf::Service::Quote>   process_limit_order(be::protobuf::Service::Quote &quote, bool from_data, bool verbose);


	// for debug
public:
	void builder();

public:
	void print();
	std::string text();
};

