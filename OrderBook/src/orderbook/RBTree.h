#pragma once

#include <boost/intrusive/link_mode.hpp>
#include <boost/algorithm/minmax_element.hpp>

#include <map>
#include <memory>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/variant/get.hpp>

class Order;
class OrderList;

typedef std::pair<int, std::shared_ptr<OrderList>> PriceValuePair;

struct my_node
{
	my_node(int i = 0);

	my_node *parent_, *left_, *right_;
	int      color_;

	//data members
	int							price_;
	std::shared_ptr<OrderList>	orderlist_;

	bool operator<(my_node const& other) const { return price_ < other.price_; }
};

//Define our own rbtree_node_traits
struct my_rbtree_node_traits
{
	typedef my_node                                    node;
	typedef my_node *                                  node_ptr;
	typedef const my_node *                            const_node_ptr;
	typedef int                                        color;
	static node_ptr get_parent(const_node_ptr n) { return n->parent_; }
	static void set_parent(node_ptr n, node_ptr parent) { n->parent_ = parent; }
	static node_ptr get_left(const_node_ptr n) { return n->left_; }
	static void set_left(node_ptr n, node_ptr left) { n->left_ = left; }
	static node_ptr get_right(const_node_ptr n) { return n->right_; }
	static void set_right(node_ptr n, node_ptr right) { n->right_ = right; }
	static color get_color(const_node_ptr n) { return n->color_; }
	static void set_color(node_ptr n, color c) { n->color_ = c; }
	static color black() { return color(0); }
	static color red() { return color(1); }
};

//namespace bi = boost::intrusive;

//using namespace boost::intrusive;

struct my_value_traits
{
	typedef my_rbtree_node_traits        node_traits;
	typedef node_traits::node            value_type;
	typedef node_traits::node_ptr        node_ptr;
	typedef node_traits::const_node_ptr  const_node_ptr;
	typedef value_type*                  pointer;
	typedef value_type const*            const_pointer;

	static const boost::intrusive::link_mode_type link_mode = boost::intrusive::link_mode_type::normal_link;

	static node_ptr       to_node_ptr(value_type &value) { return &value; }
	static const_node_ptr to_node_ptr(const value_type &value) { return &value; }
	static pointer        to_value_ptr(node_ptr n) { return n; }
	static const_pointer  to_value_ptr(const_node_ptr n) { return n; }
};

#include <boost/intrusive/rbtree.hpp>
using mytree = boost::intrusive::rbtree<my_node, boost::intrusive::value_traits<my_value_traits> >;


class RBTree
{
public:
	RBTree();
	~RBTree();

public:
	mytree container;
	std::map<int, std::shared_ptr<my_node>> my_nodes;

public:
	void insert(int price, std::shared_ptr<OrderList> order_list);
	void remove(int price);
	bool is_empty() { return my_nodes.empty();  }

	unsigned int get_min_key() { 
		auto result2 = boost::minmax_element(my_nodes.begin(), my_nodes.end());
		auto ret = (*result2.first);
		return ret.first;
	}
	unsigned int get_max_key() {
		auto result2 = boost::minmax_element(my_nodes.begin(), my_nodes.end());
		auto ret = (*result2.second);
		return ret.first;
	}

public:
	std::vector < PriceValuePair > get_data();
	void dump();
};

