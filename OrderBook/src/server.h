#pragma once

#include <queue>
#include "./orderbook/Quote.h"

class server
{
public:
	server();
	~server();

public:
	bool start();
	std::queue < Quote > queue;
};

