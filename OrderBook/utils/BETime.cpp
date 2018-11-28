#include "BETime.h"



BETime::BETime() 
{
}


BETime::~BETime()
{
}


std::chrono::milliseconds BETime::get_current_timestamp_milliseconds()
{
	//time(&timestamp);

	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		);
	return ms;

}