#pragma once

#include <vector>
#include <string>

class TestData
{
private:
	int argc;
	std::vector<std::string> argv;

public:
	TestData(int argc, char* argv[]);
	TestData() { ; }
	~TestData();

public:
	virtual  int DoTestProcess() = 0;
};

