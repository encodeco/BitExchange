#include "TestData.h"

TestData::TestData(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++) {
		this->argv.push_back(argv[i]);
	}
}


TestData::~TestData()
{
}
