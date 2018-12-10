#pragma once

#include <deque>
#include <vector>
#include <iostream>
#include "Quote.h"

class OrderTree;
class OrderList;

struct TransactionRecord {
	long			timestamp;
	unsigned int	price;
	unsigned int	quantity;
	long			time;

	struct Party1_ {
		unsigned int counter_party;
		char side;
		unsigned int order_id;
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
	std::deque < TransactionRecord >	trades;

	OrderTree							*bids;
	OrderTree							*asks;

	long								time_stamp;
	unsigned int						tick_size;
	long								time;
	unsigned int						next_order_id;

public:
	OrderBook();
	~OrderBook();

public:
	std::pair<std::vector<TransactionRecord>, Quote>  process_order( Quote &quote, bool from_data, bool verbose);
	void update_time();

	std::vector<TransactionRecord> process_market_order(Quote &quote, bool verbose);
	std::pair<std::vector<TransactionRecord>, Quote>   process_limit_order(Quote &quote, bool from_data, bool verbose);

	std::pair<unsigned int, std::vector<TransactionRecord>>  process_order_list(char side, std::shared_ptr<OrderList> order_list, unsigned int quantity_still_to_trade, Quote& quote, bool vervose);

	// for debug
public:
	void print();
	std::string text();
	BidAsk builder();
};

