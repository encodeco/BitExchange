#include <iostream>

#include "./ServerStartModule.h"
#include "./test/TestStartModule.h"

using namespace std;

int main(int argc, char* argv[])
{
	ServerStartModule sm;
	sm.run(argc, argv);

	//TestStartModule tm;
	//tm.run(argc, argv);
}







