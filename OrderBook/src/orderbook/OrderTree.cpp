#include "ordertree.h"
#include "common.h"
#include <list>
#include <memory>
#include "Order.h"
#include "OrderList.h"

OrderTree::OrderTree() : volume(0), min_price(0), max_price(0), num_orders(0), depth(0)
{
}


OrderTree::~OrderTree()
{
}

bool OrderTree::order_exists(unsigned __int64 order_id)
{
	return ( this->order_map.find(order_id) == order_map.end() ) ? false : true;
}
bool OrderTree::price_exists(unsigned __int64 price)
{
	return (this->price_map.find(price) == price_map.end() ) ? false : true;
}

void OrderTree::remove_price(unsigned __int64 price)
{
	this->depth -= 1;
	this->price_map.erase(price);
}
void OrderTree::remove_order_by_id(unsigned __int64 order_id)
{
	this->num_orders -= 1;
	auto order = this->order_map[order_id];
	this->volume -= order->get_quantity();
	order->order_list->remove_order(order);
	if (order->order_list->length() == 0) {
		this->remove_price(order->get_price());
	}
	this->order_map.erase(order_id);
	return;
}

void OrderTree::create_price(unsigned __int64 price)
{
	this->depth += 1;	 // Add a price depth level to the tree
	std::shared_ptr< OrderList>  new_list = std::make_shared<OrderList>();// Insert a new price into the tree
	this->price_map[price] = new_list;// Can i just get this by using self.price_tree.get_value(price) ? Maybe this is faster though.

	return;
}
std::shared_ptr<Order> OrderTree::insert_order(be::Quote &quote)
{
	if (order_exists(quote.mutable_order()->order_id())) {
		this->remove_order_by_id(quote.mutable_order()->order_id());
	}
	this->num_orders += 1;
	if (this->price_map.find(quote.mutable_order()->price()) == this->price_map.end()) {
		this->create_price(quote.mutable_order()->price());
	}

	std::shared_ptr<Order> order = std::make_shared<Order>(quote, this->price_map[quote.mutable_order()->price()]);

	this->price_map[order->get_price()]->append_order(order);
	this->order_map[order->get_order_id()] = order;
	this->volume += order->get_quantity();

	return order;
}


bool OrderTree::is_empty()
{
	return this->price_map.empty();
}


std::vector < PriceValuePair > OrderTree::get_data()
{
	std::vector < PriceValuePair > itemlist;

	for (auto &it : price_map) {
		std::pair<unsigned __int64, std::shared_ptr<OrderList>> item;
		item.first = (it).first;
		item.second = (it).second;
		itemlist.push_back(item);
	}
	return itemlist;
}

std::shared_ptr < OrderList > OrderTree::min_price_list() 
{
	if (this->depth > 0) {
		return this->get_price_list(this->get_min_price());
	}
	else
		return nullptr;

} 

std::shared_ptr < OrderList > OrderTree::max_price_list()
{
	if (this->depth > 0) {
		return this->get_price_list(this->get_max_price());
	}
	else
		return nullptr;

} // ko todo
unsigned __int64 OrderTree::get_min_price() {
	if (this->depth > 0) {
		return this->price_map.begin()->first;
	}
	else
		return 0;
}
unsigned __int64 OrderTree::get_max_price()
{
	if (this->depth > 0) {
		return this->price_map.rbegin()->first;
	}
	else
		return 0;
}


std::shared_ptr < OrderList> OrderTree::get_price_list(unsigned __int64 price )
{
	return this->price_map[price];
}

	