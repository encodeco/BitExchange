#include "OrderBook.h"

#include <vector>
#include <iostream>
#include <boost/range/adaptor/reversed.hpp>

#include "Order.h"
#include "OrderTree.h"
#include "OrderBook.h"
#include "OrderList.h"


OrderBook::OrderBook() : time(0), next_order_id(0), time_stamp(0), tick_size(0), bids(nullptr), asks(nullptr)
{
	bids = new OrderTree();
	asks = new OrderTree();
}


OrderBook::~OrderBook()
{
	if (bids) { delete bids; bids = nullptr; }
	if (asks) { delete asks; asks = nullptr; }
}

void OrderBook::update_time()
{
	this->time += 1;
}

std::pair<unsigned int, std::vector<TransactionRecord>>  OrderBook::process_order_list(be::protobuf::Service::Quote &quote, char side, std::shared_ptr<OrderList> order_list, unsigned int quantity_still_to_trade, bool verbose)
{
	//Takes an OrderList(stack of orders at one price) and an incoming order and matches
	//	appropriate trades given the order's quantity.
	pair<unsigned int, std::vector<TransactionRecord>> return_value;

	std::vector<TransactionRecord> trades;
	unsigned int quantity_to_trade = quantity_still_to_trade;


	while (order_list->length() > 0 && quantity_to_trade > 0)
	{
		// 두번째로 불려질땐, 처리할 쿼트에 양이 남아 있고, 첫번째 오더는 지워진상태이다.
		auto head_order = order_list->get_head_order();
		auto traded_price = head_order->get_price();
		auto counter_party = head_order->get_trade_id();
		unsigned int traded_quantity = 0;

		unsigned int new_book_quantity = 0;
		// 쿼트에 양보다 오더북속 오더에 양이 큰경우 --> 쿼트 양 0으로 만들고, 오더북속 오더에 양은 줄인다.
		if (quantity_to_trade < head_order->get_quantity()) {
			traded_quantity = quantity_to_trade;
			// Do the transaction
			new_book_quantity = head_order->get_quantity() - quantity_to_trade;
			head_order->update_quantity(new_book_quantity, head_order->get_timestamp());
			quantity_to_trade = 0;
		}
		// 쿼트 양과 오더북속 오더에 야이 같은경우 --> 쿼트 지우고, 오더북속 오더도 지워져야한다.
		else if (quantity_to_trade == head_order->get_quantity()) {
			traded_quantity = quantity_to_trade;
			if (side == 'B')
				this->bids->remove_order_by_id(head_order->get_order_id());
			else
				this->asks->remove_order_by_id(head_order->get_order_id());
			quantity_to_trade = 0;
		}
		// 쿼트에 양이 오더북속 오더에 양보다 많은 경우 --> 오더북속 오더는 지우고, 쿼트는 업데이트 시킨다.
		else {
			// quantity to trade is larger than the head order
			traded_quantity = head_order->get_quantity();
			if (side == 'B') {
				this->bids->remove_order_by_id(head_order->get_order_id());
			}
			else {
				this->asks->remove_order_by_id(head_order->get_order_id());
			}
			quantity_to_trade -= traded_quantity;
		}

		if (verbose) {
			//print(("TRADE: Time - {}, Price - {}, Quantity - {}, TradeID - {}, Matching TradeID - {}".format(self.time, traded_price, traded_quantity, counter_party, quote['trade_id'])))
		}

		TransactionRecord transaction_record;
		transaction_record.timestamp = this->time;
		transaction_record.price = traded_price;
		transaction_record.quantity = traded_quantity;;
		transaction_record.time = this->time;

		if (side == 'B') {
			transaction_record.party1.counter_party = counter_party;
			transaction_record.party1.side = 'B';
			transaction_record.party1.order_id = head_order->get_order_id();
			transaction_record.party1.book_quantity = new_book_quantity;
			transaction_record.party2.trade_id = quote.mutable_order()->trader_id();
			transaction_record.party2.side = 'A';
		}
		else {
			transaction_record.party1.counter_party = counter_party;
			transaction_record.party1.side = 'A';
			transaction_record.party1.order_id = head_order->get_order_id();
			transaction_record.party1.book_quantity = new_book_quantity;
			transaction_record.party2.trade_id = quote.mutable_order()->trader_id();
			transaction_record.party2.side = 'B';
		}

		this->tape.push_back(transaction_record);
		trades.push_back(transaction_record);
	}
	return_value.first = quantity_to_trade;
	return_value.second = trades;
	return return_value;
}

std::vector<TransactionRecord> OrderBook::process_market_order(be::protobuf::Service::Quote &quote, bool verbose)
{
	std::vector<TransactionRecord> trades;

	unsigned int quantity_to_trade = quote.mutable_order()->quantity();
	char order_side = quote.order_side().c_str()[0];
	
	if (order_side == 'B') {
		while (quantity_to_trade > 0 && this->asks->length()) {
			auto best_price_asks = this->asks->min_price_list();
			auto value = this->process_order_list(quote, 'A', best_price_asks, quantity_to_trade, verbose);
			quantity_to_trade = value.first;
			auto new_trades = value.second;
			trades.insert(trades.end(), new_trades.begin(), new_trades.end());
		}
	}
	else if (order_side == 'A') {
		while (quantity_to_trade > 0 && this->bids->length()) {
			auto best_price_bids = this->bids->max_price_list();
			auto value = this->process_order_list(quote, 'B', best_price_bids, quantity_to_trade, verbose);
			quantity_to_trade = value.first;
			auto new_trades = value.second;
			trades.insert(trades.end(), new_trades.begin(), new_trades.end());
		}
	}
	else {
		//sys.exit('process_market_order() recieved neither "bid" nor "ask"')
		return trades;
	}

	return trades;	
}

std::pair<std::vector<TransactionRecord>, be::protobuf::Service::Quote>   OrderBook::process_limit_order(be::protobuf::Service::Quote &quote, bool from_data, bool verbose)
{

	std::pair<std::vector<TransactionRecord>, be::protobuf::Service::Quote> return_value;

	be::protobuf::Service::Quote order_in_book;
	std::vector< TransactionRecord > trades;
	unsigned int quantity_to_trade = quote.mutable_order()->quantity();
	char side = quote.order_side().c_str()[0];
	unsigned int price = quote.mutable_order()->price();
	if (side == 'B') { // 사자 쿼트가 입력된경우

		// 입력 쿼트가 BID (BUY)일 경우,  ASK (SELL)트리에서 가장 낮은 가격(get_min_price)을 꺼내와서 이력된 쿼트와 비교한다.
		// 팔자 오더북중, 가장 낮은 가격에 팔려는 오더부터 처리한다. ( # PRICE우선 )
		while (this->asks->length() && price >= this->asks->get_min_price() && quantity_to_trade > 0) {
			auto best_price_asks = this->asks->min_price_list();

			// 가장 낮은 가격에 걸려있는 오더 리스트(best_price_asks)와 매칭시킨다. ( # 시간 우선 )
			auto value = this->process_order_list(quote, 'A', best_price_asks, quantity_to_trade, verbose);

			quantity_to_trade = value.first;
			auto new_trades = value.second;

			trades.insert(trades.end(), new_trades.begin(), new_trades.end());
		}

		// If volume remains, need to update the book with new quantity
		if (quantity_to_trade > 0) {
			if (!from_data) {
				quote.mutable_order()->set_order_id( this->next_order_id );
			}
			quote.mutable_order()->set_quantity( quantity_to_trade );
			this->bids->insert_order(quote);
			order_in_book.CopyFrom( quote );
		}
	}
	else if (side == 'A') { // 팔자 쿼트가 입력된경우

		// 입력 쿼트가 ASK (SELL)일 경우, BID (BUY) 트리에서 가장 높은 가격(get_max_price)을 꺼내와서 이력된 쿼트와 비교한다.
		// 사자 오더북중, 가장 높은 가격에 사려는 오더부터 처리한다.
		while (!this->bids->is_empty() && this->bids->get_max_price() && quantity_to_trade > 0) {
			auto best_price_bids = this->bids->max_price_list();
			auto value = this->process_order_list( quote, 'B', best_price_bids, quantity_to_trade, verbose);

			quantity_to_trade = value.first;
			auto new_trades = value.second;

			trades.insert(trades.end(), new_trades.begin(), new_trades.end());
		}
		//If volume remains, need to update the book with new quantity
		if (quantity_to_trade > 0) {
			if (!from_data) {
				quote.mutable_order()->set_order_id( this->next_order_id );
			}
			quote.mutable_order()->set_quantity( quantity_to_trade );
			this->asks->insert_order(quote);
			order_in_book.CopyFrom(quote);
		}
	}
	else {
		//sys.exit('process_limit_order() given neither "bid" nor "ask"')
		return return_value;
	}

	return_value.first = trades;
	return_value.second = order_in_book;
	return return_value;
}

std::pair<std::vector<TransactionRecord>, be::protobuf::Service::Quote> OrderBook::process_order(be::protobuf::Service::Quote &quote, bool from_data, bool verbose)
{
	const char order_type = quote.order_type().c_str()[0];

	be::protobuf::Service::Quote order_in_book;

	if (from_data)
		this->time = quote.mutable_order()->timestamp();
	else {
		this->update_time();
		quote.mutable_order()->set_timestamp( this->time );
	}

	std::pair<std::vector<TransactionRecord>, be::protobuf::Service::Quote> return_value;

	if (quote.mutable_order()->timestamp() <= 0) {
		//sys.exit('process_order() given order of quantity <= 0')
		return return_value;
	}
	if (!from_data) {
		this->next_order_id += 1;
	}

	std::vector< TransactionRecord > trades;

	if (order_type == 'M') {
		trades = this->process_market_order(quote, verbose);
	}
	else if (order_type == 'L') {
		auto limit_order_result = this->process_limit_order(quote, from_data, verbose);
		trades = limit_order_result.first;
		order_in_book.CopyFrom( limit_order_result.second );
	}
	else {
		//sys.exit("order_type for process_order() is neither 'market' or 'limit'")
		return return_value;
	}


	return_value.first = trades;
	return_value.second = order_in_book;

	return return_value;
}


void OrderBook::print() 
{
	std::cout << "***Bids***" << endl;
	if (!this->bids->is_empty()) {
		auto data = this->bids->get_data();
		for (auto a_data : boost::adaptors::reverse(data)) {
			auto a_key = a_data.first;
			auto a_value = a_data.second;
			(*a_value).print();
		}
	}

	std::cout << "***Asks***" << endl;
	if (!this->asks->is_empty()) {
		auto data = this->asks->get_data();
		for (auto a_data : data) {
			auto a_key = a_data.first;
			auto a_value = a_data.second;
			(*a_value).print();
		}
	}


	std::cout << "***Trades***" << endl;
	
	if (!this->tape.empty()) {
		int num = 0;
		for (auto entry : this->tape) {
			if (num < 10) // get last 5 entries
			{
				//tempfile.write(str(entry['quantity']) + " @ " + str(entry['price']) + " (" + str(entry['timestamp']) + ") " + str(entry['party1'][0]) + "/" + str(entry['party2'][0]) + "\n")

				cout << entry.quantity << " @ " << entry.price << " ( " << entry.timestamp << +" ) " << entry.party1.counter_party << " / " << entry.party2.trade_id << endl;
				num += 1;
			}
			else
				break;
		}
	}
	
}

void OrderBook::builder()
{
	BidAsk bidask;
/*
	PriceQuantityVec &bid = bidask.first;
	PriceQuantityVec &ask = bidask.second;
	
	std::string rstr;
	rstr += "***Bids*** \n";
	if (!this->bids->is_empty()) {
		auto data = this->bids->get_data();
		for (auto a_data : boost::adaptors::reverse(data)) {
			PriceQuantity pq;

			auto a_price_key = a_data.first;
			auto a_value = a_data.second;

			pq.first = a_price_key;
			pq.second = (*a_value).quantity_sum();

			bid.push_back(pq);
		}
	}

	rstr += "***Asks*** \n";
	if (!this->asks->is_empty()) {
		auto data = this->asks->get_data();
		for (auto a_data : data) {
			PriceQuantity pq;

			auto a_price_key = a_data.first;
			auto a_value = a_data.second;

			pq.first = a_price_key;
			pq.second = (*a_value).quantity_sum();

			bid.push_back(pq);
		}
	}
*/
	//return bidask;
}
std::string OrderBook::text()
{
	std::string rstr;
	rstr += "***Bids*** \n";
	if (!this->bids->is_empty()) {
		auto data = this->bids->get_data();
		for (auto a_data : boost::adaptors::reverse(data)) {
			auto a_key = a_data.first;
			auto a_value = a_data.second;
			rstr += (*a_value).text();
		}
	}

	rstr += "***Asks*** \n";
	if (!this->asks->is_empty()) {
		auto data = this->asks->get_data();
		for (auto a_data : data) {
			auto a_key = a_data.first;
			auto a_value = a_data.second;
			rstr += (*a_value).text();
		}
	}


	rstr += "***Trades*** \n";

	if (!this->tape.empty()) {
		int num = 0;
		for (auto entry : this->tape) {
			if (num < 10) // get last 5 entries
			{
				//tempfile.write(str(entry['quantity']) + " @ " + str(entry['price']) + " (" + str(entry['timestamp']) + ") " + str(entry['party1'][0]) + "/" + str(entry['party2'][0]) + "\n")

				rstr += entry.quantity;
				rstr += " @ ";
				rstr += (unsigned int)entry.price;
				rstr += " ( ";
				rstr += (unsigned int)entry.timestamp;
				rstr += " ) ";
				rstr += entry.party1.counter_party;
				rstr += " / ";
				rstr += entry.party2.trade_id;
				rstr += "\n";
				num += 1;
			}
			else
				break;
		}
	}
	return rstr;

}