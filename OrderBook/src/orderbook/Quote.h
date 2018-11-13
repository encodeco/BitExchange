#pragma once

#include "common.h"
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>  

class Quote {
public:
	char			order_type;
	char			order_side;
	unsigned int	quantity;
	unsigned int	price;
	unsigned int	order_id;
	time_t			timestamp;
	unsigned int	trade_id;

public:
	Quote();
	Quote(std::vector< std::string > &quote_string);
	~Quote();

public:
	std::string redis_set_hash_string(size_t order_id, time_t timestamp);
	std::string redis_set_list_string(size_t order_id, time_t timestamp);
	bool fromText(std::vector< std::string > &quote_string);
	time_t set_current_timestamp();
};

