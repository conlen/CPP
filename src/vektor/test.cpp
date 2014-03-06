#include <iostream>
#include "vektor.hpp"

using namespace std;

void test1()
{
	return;
}

int main(int argc, char *argv[])
{
	int 		rc;
	struct rusage	ru;
	double			startTime, endTime;
	double 			r;


	cout << "main start" << endl;

	test1();


	return(0);
}