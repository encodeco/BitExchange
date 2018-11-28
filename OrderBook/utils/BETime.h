#pragma once
#include <iostream>
#include <chrono>

#define TIMING

#ifdef TIMING
#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now();
#define START_TIMER  start = std::chrono::high_resolution_clock::now();
#define STOP_TIMER(name)  std::cout << "RUNTIME of " << name << ": " << \
    std::chrono::duration_cast<std::chrono::milliseconds>( \
            std::chrono::high_resolution_clock::now()-start \
    ).count() << " ms " << std::endl; 
#else
#define INIT_TIMER
#define START_TIMER
#define STOP_TIMER(name)
#endif

class BETime
{
public:
	BETime();
	~BETime();

public:
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	std::chrono::duration<double> time_span;

	static time_t get_current_timestamp();
	std::chrono::milliseconds get_current_timestamp_milliseconds();

	std::chrono::high_resolution_clock::time_point start() {
		t1 = std::chrono::high_resolution_clock::now();
		return t1;
	}

	std::chrono::high_resolution_clock::time_point stop() {
		t2 = std::chrono::high_resolution_clock::now();
		time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
		return t2;
	}

	std::chrono::duration<double>  diff() {
		return time_span;
	}
	

};

