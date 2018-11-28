#include "redispp.h"

#pragma comment(lib, "hiredis.lib")
#pragma comment(lib, "Win32_Interop.lib")

#include <iostream>

//
//if (redis.resp == NULL)
//return 0;
//
//// error
//if (redis.resp->type != REDIS_REPLY_ERROR) {
//
//
//}
void *redispp::redisCommand(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	this->resp = (redisReply *)redisvCommand(conn, format, ap);
	va_end(ap);

	if (this->resp == nullptr) {
		throw(0);
	}
	if (this->resp->type == REDIS_REPLY_ERROR) {
		this->free_reply_object();
		throw(0);
	}

	return this->resp;
}

redispp::redispp() : conn(nullptr), resp(nullptr), errorstring(""), success(false)
{
}
bool redispp::connect(const char *server_addr, int port)
{
	// connect
	conn = redisConnect("127.0.0.1", 6379);

	if ((NULL != conn) && conn->err) {
		// error
		std::cout << "error : " << conn->errstr << std::endl;
		errorstring = conn->errstr;
		return false;
	}
	else if (NULL == conn) {
		errorstring = "conn is null";
		return false;
	}
	success = true;
	return true;
}


redispp::~redispp()
{
	if (conn) {
		redisFree(conn);
		conn = nullptr;
	}
}

void redispp::free_reply_object()
{
	if (resp) {
		freeReplyObject(resp);
		resp = nullptr;
	}
}