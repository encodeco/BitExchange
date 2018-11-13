#pragma once
#include <map>
#include <memory>
#include "RBTree.h"

class OrderList;
class RBTree;
class Order; 
class Quote;

using namespace std;
class OrderTree
{
private:
	RBTree											*price_tree;
	unsigned int									volume;

	map< unsigned int, std::shared_ptr<OrderList> > price_map; // key : price
	map< unsigned int, std::shared_ptr<Order> >		order_map; // key : id num

	unsigned int									min_price;
	unsigned int									max_price;
	unsigned int									num_orders;

	unsigned int									depth;


public:
	OrderTree();
	~OrderTree();

public:
	int length() { return this->order_map.size(); }
	bool is_empty();
	std::shared_ptr < OrderList > min_price_list();
	std::shared_ptr < OrderList > max_price_list();

	std::shared_ptr < OrderList> get_price_list(unsigned int price);
	unsigned int get_min_price();
	unsigned int get_max_price();

	void remove_order_by_id(unsigned int order_id);
	void remove_price(unsigned int price);

	void insert_order( Quote &quote );
	bool order_exists(unsigned int order_id);
	bool price_exists(unsigned int price);
	void create_price(unsigned int price);
	void update_order(Order* update);


	std::vector < PriceValuePair > get_data();
};

