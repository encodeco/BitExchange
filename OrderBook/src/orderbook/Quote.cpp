#include "Quote.h"

#include <boost/format.hpp>
#include <time.h>

using namespace std;

Quote::Quote() : order_type('N'), order_side('N'), quantity(0), price(0), order_id(0), timestamp(0), trade_id(0)
{ 
}
Quote::Quote(std::vector< std::string > &quote_string) {
	this->fromText(quote_string);
}
Quote::~Quote() 
{
}

std::string Quote::redis_set_list_string(size_t order_id, time_t timestamp)
{
	string str = "SADD order ";
	str += std::to_string(this->order_id);
	str += ",";
	str += std::to_string(this->order_type);
	str += ",";
	str += std::to_string(this->order_side);
	str += ",";
	str += std::to_string(this->quantity);
	str += ",";
	str += std::to_string(this->price);
	str += ",";
	str += std::to_string(this->trade_id);
	str += ",";
	str += std::to_string(this->timestamp);
	return str;
}
std::string Quote::redis_set_hash_string(size_t order_id, time_t timestamp) 
{
	string str = "";
	str += (boost::format("HMSET order_id:%1%") % timestamp).str();
	str += " ";
	str += (boost::format("type %1%") % order_type).str();
	str += " ";
	str += (boost::format("side %1%") % order_side).str();
	str += " ";
	str += (boost::format("quantity %1%") % quantity).str();
	str += " ";
	str += (boost::format("price %1%") % price).str();
	str += " ";
	str += (boost::format("trade_id %1%") % trade_id).str();
	str += " ";
	str += (boost::format("timestamp %1%") % timestamp).str();

	return str;
}
bool Quote::fromText(std::vector< std::string > &quote_string) {
	try {
		order_type = boost::algorithm::to_upper_copy(quote_string[TC_TYPE])[0];
		order_side = boost::algorithm::to_upper_copy(quote_string[TC_SIDE])[0];
		quantity = std::stoi(quote_string[TC_QUANTITY]);
		price = std::stoi(quote_string[TC_PRICE]);
		trade_id = std::stoi(quote_string[TC_ID]);
		timestamp = std::stol(quote_string[TC_TIMESTAMP]);
		order_id = 0;
	}
	catch (...) {
		return false;
	}

	return true;
}	

time_t Quote::set_current_timestamp()
{
	time(&timestamp);
	return timestamp;
}