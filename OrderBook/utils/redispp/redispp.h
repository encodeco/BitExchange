#pragma once
#include <string>

#include "hiredis/hiredis.h"

class redispp
{
public:
	redispp();
	~redispp();

	bool connect(const char *server_addr, int port);
	void *redisCommand(const char *format, ...);
	void free_reply_object();
	bool success;

public:
	redisContext *conn;
	redisReply *resp;
	std::string errorstring;
	bool	is_success() {
		return success;
	}
};

