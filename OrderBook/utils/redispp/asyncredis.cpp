#include "asyncredis.h"

#include <hiredis/hiredis.h>
#include <hiredis/async.h>
//#include <hiredis/adapters/libevent.h>

//#pragma comment(lib, "hiredis.lib")
//#pragma comment(lib, "Win32_Interop.lib")

asyncredis::asyncredis()
{
}


asyncredis::~asyncredis()
{
}

bool asyncredis::connect() {
	//c = redisAsyncConnect("localhost", 6379);

	return true;
}