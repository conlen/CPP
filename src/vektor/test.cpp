#include <iostream>
#include "vektor.hpp"

using namespace std;

void test1()
{

	vektor<float>		x;
	std::vector<float> 	v = {1.0, 2.0, 3.0};

	cout << "test1" << endl;
	x = v;
	cout << "x = " << x << endl;
	cout << "end test1" << endl;
	return;
}

int main(int argc, char *argv[])
{
	int 		rc;

	cout << "main start" << endl;

	test1();


	return(0);
}