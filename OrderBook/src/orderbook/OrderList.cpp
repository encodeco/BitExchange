#include "OrderList.h"
#include <iostream>
#include <algorithm>
#include "Order.h"

OrderList::OrderList() : volume(0)
{
}


OrderList::~OrderList()
{
}

void OrderList::append_order(std::shared_ptr<Order> order) {
	this->volume += order->get_quantity();
	order_list.push_back(order);
}


void OrderList::remove_order(std::shared_ptr<Order> order) {
	this->volume -= order->get_quantity();
	order_list.remove(order);
}

void OrderList::print()
{
	for (auto order : order_list) {
		order->print();
	}
}
std::string OrderList::text()
{
	std::string rstr;
	for (auto order : order_list) {
		rstr += order->text();
	}
	return rstr;
}


void OrderList::move_to_tail(Order* order) {

	// ko todo
	for (auto an_order : order_list) {
		if (an_order->get_order_id() == order->get_order_id()) {
			order_list.remove(an_order);
			order_list.push_back(an_order);
		}
	}
}
size_t OrderList::quantity_sum() {
	PriceQuantityVec orderlist;
	std::string rstr;

	size_t quantity_sum = 0;
	for (auto order : order_list) {
		quantity_sum += order->get_quantity();
	}
	return quantity_sum;
}
//std::ostream& operator<< (std::ostream& out, const OrderList& obj)
//{
//	auto order_list = obj.get_order_list();
//	for (auto order : order_list) {
//		out << order;
//	}
//	//out << "OrderList";
//	return out;
//}