#pragma once

#include "common.h"
#include <string>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>  

#include <chrono>

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
	Quote(std::map <std::string, std::string> &mapitems);
	~Quote();
	
public:
	std::string redis_set_hash_string(size_t order_id, time_t timestamp);
	std::string redis_set_list_string(size_t order_id, time_t timestamp);
	bool fromText(std::vector< std::string > &quote_string);
	bool fromMap(std::map <std::string, std::string> &mapitems);
	time_t set_current_timestamp();

	std::string to_text();

};

