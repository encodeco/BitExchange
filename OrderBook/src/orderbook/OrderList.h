#pragma once
#include <list>
#include <memory>

class Order;

class OrderList
{
private:
	std::list<std::shared_ptr<Order>> order_list;
	unsigned int volume;

public:
	OrderList();
	~OrderList();

public:
	std::shared_ptr<Order> get_head_order() { return *(order_list.begin()); }
	std::shared_ptr<Order> get_tail_order() { return *(std::next(order_list.end(), -1)); }
	unsigned int length() { return order_list.size(); }
	bool is_exist() { return order_list.empty(); }
	void append_order(std::shared_ptr<Order> order);
	void remove_order(std::shared_ptr<Order> order);

	void set_volume(unsigned int volume) { this->volume = volume; }
	unsigned int get_volume() { return this->volume; }

	void move_to_tail(Order* order);

	const std::list<std::shared_ptr<Order>> &get_order_list() {
		return order_list;
	}
	void print();
	std::string text();
	size_t quantity_sum();
};
