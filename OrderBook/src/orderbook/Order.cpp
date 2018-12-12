#include "Order.h"
#include <iostream>
#include <boost/format.hpp>
#include <string>

#include "OrderList.h"


Order::Order()
{
}

Order::Order(Service::Quote &quote, std::shared_ptr<OrderList> order_list)
{
	this->timestamp = quote.mutable_order()->timestamp();
	this->quantity = quote.mutable_order()->quantity();
	this->price = quote.mutable_order()->price();
	this->order_id = quote.mutable_order()->order_id();
	this->trade_id = quote.mutable_order()->trader_id();

	this->order_list = order_list;
}

Order::~Order()
{
}


void Order::update_quantity(unsigned int new_quantity, time_t new_timestamp)
{
	if (new_quantity > this->quantity && this->order_list->get_tail_order()->get_order_id() != this->get_order_id()) {
		// check to see that the order is not the last order in list and the quantity is more
		this->order_list->move_to_tail(this);
	}

	this->order_list->set_volume(this->order_list->get_volume() - (this->quantity - new_quantity)); //update volumn
	this->timestamp = new_timestamp;
	this->quantity = new_quantity;
}

void Order::print()
{
	cout << boost::format("%1% @ %2% / %3%  -  %4%") % this->quantity % this->price % this->trade_id % this->timestamp << endl;
}
std::string Order::text()
{
	std::string rstr;
	rstr = str(
		boost::format("%1% @ %2% / %3%  -  %4% \n") % this->quantity % this->price % this->trade_id % this->timestamp
		);
	return rstr;
}


PriceQuantity Order::get_price_quantity()
{
	PriceQuantity output;
	output.first = this->price;
	output.second = this->quantity;
	return output;
}