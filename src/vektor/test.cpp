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
	if((rc = getrusage(RUSAGE_SELF, &ru)) != 0) { perror("getrusage 1");}
	startTime = ru.ru_utime.tv_sec + ru.ru_stime.tv_sec + ((long double)(ru.ru_utime.tv_usec + ru.ru_stime.tv_sec)) / 1000000;

	test1();

	if((rc = getrusage(RUSAGE_SELF, &ru)) != 0) { perror("getrusage 1");}
	endTime = ru.ru_utime.tv_sec + ru.ru_stime.tv_sec + ((long double)(ru.ru_utime.tv_usec + ru.ru_stime.tv_sec)) / 1000000;
	cout << "Computed " << r << " in " << endTime - startTime << endl;
	return(0);
}