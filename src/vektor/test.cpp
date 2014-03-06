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

void test2()
{
	std::vector<double>	v = {1.0, 2.0, 3.0};
	vektor<double>		x(v);
	cout << "test2" << endl;
	cout << "x = " << x << endl;
	cout << "end test2" << endl;
	return;
}

int main(int argc, char *argv[])
{
	int 		rc;

	cout << "main start" << endl;

	test1();
	test2();

	return(0);
}