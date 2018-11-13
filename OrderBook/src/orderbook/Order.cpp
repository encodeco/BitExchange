#include "Order.h"
#include "Quote.h"
#include <iostream>
#include <boost/format.hpp>
#include <string>

#include "OrderList.h"

Order::Order()
{
}
Order::Order(Quote &quote, std::shared_ptr<OrderList> order_list)
{
	this->timestamp = quote.timestamp;
	this->quantity = quote.quantity;
	this->price = quote.price;
	this->order_id = quote.order_id;
	this->trade_id = quote.trade_id;

	this->order_list = order_list;
}

Order::~Order()
{
}


void Order::update_quantity(unsigned int new_quantity, long new_timestamp)
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
	cout << boost::format("%1% @ %2% / %3%  -  %4%") % this->quantity % this->price % this->trade_id % this->timestamp << endl ;
}

//ostream& Order::operator<<(ostream& os, const Order& order)
//{
//	//os << dt.mo << '/' << dt.da << '/' << dt.yr;
//	os << boost::format("%1% %2% %3% %4%") % order.quantity % order.price % order.trade_id % order.timestamp << endl;
//	return os;
//}

//ostream& operator<< (ostream& os, const Order& order) {
//	os << "order";
//	return os;
//}

//std::ostream& operator<<(std::ostream &out, const Order& order) {
//	out << "Order";
//	return out;
//}