#pragma once

#include <deque>
#include <vector>
#include <iostream>

#include "./protobuf/Trading.pb.h"

class OrderTree;
class OrderList;

//using be::protobuf::Service;

struct TransactionRecord {
	time_t				timestamp;
	unsigned __int64	price;
	unsigned int		quantity;

	struct Party1_ {
		unsigned int counter_party;
		char side;
		unsigned __int64 order_id;
		unsigned int book_quantity;
	}party1;

	struct Party2 {
		unsigned int trader_id;
		char side;
	}party2;

	void print() {
		std::cout << party2.trader_id << " " <<  party1.side << std::endl;
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

	std::pair<unsigned int, std::vector<TransactionRecord>>  process_order_list(be::Quote &quote, char side, std::shared_ptr<OrderList> order_list, unsigned int quantity_still_to_trade, bool verbose);
	std::pair<std::vector<TransactionRecord>, be::Quote> process_order( be::Quote &quote, bool from_data, bool verbose);
	void update_time();

	std::vector<TransactionRecord> process_market_order(be::Quote &quote, bool verbose);
	std::pair<std::vector<TransactionRecord>, be::Quote>   process_limit_order(be::Quote &quote, bool from_data, bool verbose);


	// for debug
public:
	void builder();

public:
	void print();
	std::string text();
	void get_orderbook(be::OrderBook &orderbook);
};

