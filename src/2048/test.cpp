#include <cstdint>
#include <cstring>
#include <iostream>

#include "2048.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	tofe<0>	t;

	cout << "tests pass == 1 == " << t.runTests() << endl;
	return(0);
}