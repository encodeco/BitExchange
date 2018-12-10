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
	long						timestamp;
	unsigned int				quantity;
	unsigned int				price;
	unsigned int				order_id;
	unsigned int				trade_id;

public:
	std::shared_ptr<OrderList>				order_list;

public:
	Order();
	Order(Quote &quote, std::shared_ptr<OrderList> order_list);
	~Order();

public:
	unsigned int get_order_id() { return order_id; }
	unsigned int get_trade_id() { return trade_id; }
	unsigned int get_quantity() { return quantity; }
	unsigned int get_price() { return price; }
	unsigned int get_timestamp() { return timestamp; }

	void update_quantity(unsigned int new_quantity, long new_timestamp);


public:
	void  print();
	std::string  text();
	PriceQuantity get_price_quantity();
	//friend ostream& operator<<(ostream& os)
	//{
	//	//os << dt.mo << '/' << dt.da << '/' << dt.yr;
	//	//os << boost::format("%1% %2% %3% %4%") % this->quantity % order.price % order.trade_id % order.timestamp << endl;
	//	os << "ORDER";
	//	return os;
	//}
	//friend std::ostream& operator<<(std::ostream&, const Order&);
};
