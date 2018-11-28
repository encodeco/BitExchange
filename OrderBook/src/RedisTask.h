#pragma once

#include "utils/Stoppable.h"
#include <thread>
#include <mutex>
#include <condition_variable>

#include "./orderbook/Quote.h"

class RedisTask : public Stoppable
{
public:
	std::deque< Quote > quotes;
	std::mutex mu;
	std::condition_variable cond;

public:
	void run();
	void run2();

public:
	void safe_insert(Quote quote);
	bool safe_pop(Quote &quote);
};
