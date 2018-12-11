#pragma once
#include "common.h"
#include <memory>
#include <vector>
#include <list>

using namespace std;

class OrderList;
class Quote;

class Order
{
private:
	unsigned __int64				price;
	unsigned __int64				order_id;
	unsigned int					quantity;
	unsigned int					trade_id;
	time_t							timestamp;

public:
	std::shared_ptr<OrderList>				order_list;

public:
	Order();
	Order(Quote &quote, std::shared_ptr<OrderList> order_list);
	~Order();

public:
	unsigned __int64 get_order_id() { return order_id; }
	unsigned int get_trade_id() { return trade_id; }
	unsigned int get_quantity() { return quantity; }
	unsigned __int64 get_price() { return price; }
	time_t get_timestamp() { return timestamp; }

	void update_quantity(unsigned int new_quantity, time_t new_timestamp);


public:
	void  print();
	std::string  text();
	PriceQuantity get_price_quantity();
};
