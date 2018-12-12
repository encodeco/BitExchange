#pragma once
#include <map>
#include <memory>
#include "common.h"
#include "./protobuf/Service.pb.h"

class OrderList;
class RBTree;
class Order; 
class Quote;

using namespace std;


typedef std::pair<unsigned __int64, std::shared_ptr<OrderList>> PriceValuePair;

class OrderTree
{
private:
	map< unsigned __int64, std::shared_ptr<OrderList> > price_map; // key : price
	map< unsigned __int64, std::shared_ptr<Order> >		order_map; // key : id num

	unsigned int										volume;

	unsigned __int64									min_price;
	unsigned __int64									max_price;
	unsigned int										num_orders;

	unsigned int										depth;


public:
	OrderTree();
	~OrderTree();

public:
	int length() { return this->order_map.size(); }
	bool is_empty();
	std::shared_ptr < OrderList > min_price_list();
	std::shared_ptr < OrderList > max_price_list();

	std::shared_ptr < OrderList> get_price_list(unsigned __int64 price);
	unsigned __int64 get_min_price();
	unsigned __int64 get_max_price();

	void remove_order_by_id(unsigned __int64 order_id);
	void remove_price(unsigned __int64 price);

	void insert_order( be::protobuf::Service::Quote &quote );
	bool order_exists(unsigned __int64 order_id);
	bool price_exists(unsigned __int64 price);
	void create_price(unsigned __int64 price);

	std::vector < PriceValuePair > get_data();
};

