#pragma once


#include "hiredis/async.h"

class asyncredis
{
public:
	redisAsyncContext *c;

public:
	asyncredis();
	~asyncredis();

public:
	bool connect();
};

