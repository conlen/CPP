#include <iostream>
#include "vektor.hpp"

using namespace std;

void test1()
{

	vektor<float>	x;

	cout << "test1" << endl;

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