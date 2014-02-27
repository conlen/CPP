#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <sys/resource.h>
#include <sys/time.h>

using namespace std;

template<typename T, typename U>
T dot(vector<T> x, vector<U> y) 
{
	int		i;
	double	r = 0;

	for(i=0; i<x.size(); i++) { r+= x[i]*y[i]; }
	return(r);
}


int main(int argc, char *argv[])
{
	int 		rc;
	struct rusage	ru;
	double			startTime, endTime;
	vector<double> 	x = {1.0, 2.0, 3.0}, y = {4.0, 5.0, 6.0};
	vector<float>	x2 = {11.0, 2.0, 3.0}, y2 = {41.0, 5.0, 6.0};
	double 			r;


	if((rc = getrusage(RUSAGE_SELF, &ru)) != 0) { perror("getrusage 1");}
	startTime = ru.ru_utime.tv_sec + ru.ru_stime.tv_sec + ((long double)(ru.ru_utime.tv_usec + ru.ru_stime.tv_sec)) / 1000000;

	r = dot(x, y);
	cout << r << endl;

	r = dot(x2, y2);
	cout << r << endl;

	r = dot<float, double>(x2, y);
	cout << r << endl;

	if((rc = getrusage(RUSAGE_SELF, &ru)) != 0) { perror("getrusage 1");}
	endTime = ru.ru_utime.tv_sec + ru.ru_stime.tv_sec + ((long double)(ru.ru_utime.tv_usec + ru.ru_stime.tv_sec)) / 1000000;
	cout << "Computed " << r << " in " << endTime - startTime << endl;
	return(0);
}