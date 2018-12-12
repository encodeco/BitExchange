#pragma once

#include "utils/Stoppable.h"
#include <thread>
#include <mutex>
#include <condition_variable>

#include "./protobuf/Service.pb.h"

class RedisTask : public Stoppable
{
public:
	RedisTask();
	~RedisTask();

public:
	//std::mutex mu;
	std::condition_variable cond;

public:
	void run();
	void run(be::protobuf::Service::QuoteList &quotes, std::mutex &mu);

};
