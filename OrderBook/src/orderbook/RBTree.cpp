#include "RBTree.h"

#include <vector>
#include <iostream>
#include "OrderList.h"

my_node::my_node(int i) :
	parent_(nullptr),
	left_(nullptr),
	right_(nullptr),
	orderlist_(nullptr),
	price_(i)
{
}

RBTree::RBTree()
{
	//container
}


RBTree::~RBTree()
{
}

void RBTree::remove(int price)
{
	container.erase(price);
	my_nodes.erase(price);
}
void RBTree::insert(int price, std::shared_ptr<OrderList> order_list)
{
	std::shared_ptr<my_node> node = std::make_shared<my_node>();
	node->price_ = price;
	node->orderlist_ = order_list;
	container.insert_equal(*node);

	my_nodes[price] = node;
}

// for debugging. slow!
std::vector < PriceValuePair > RBTree::get_data()
{
	std::vector < PriceValuePair > itemlist;

	for (auto &it : container) {
		std::pair<int, std::shared_ptr<OrderList>> item;
		item.first = (it).price_;
		item.second = (it).orderlist_;
		itemlist.push_back(item);
	}	
	return itemlist;
}

void RBTree::dump()
{
	for (my_node& n : container) {
		std::cout << n.price_ << "," << &n
			<< " (parent: " << n.parent_->price_ << "," << n.parent_ << ")"
			<< " (left:   " << (n.left_ ? n.left_->price_ : 0) << "," << n.left_ << ")"
			<< " (right:  " << (n.right_ ? n.right_->price_ : 0) << "," << n.right_ << ")"
			<< "\n";
	}
}