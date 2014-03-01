#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "vektor.hpp"

#include <sys/resource.h>
#include <sys/time.h>

using namespace std;


void test1()
{
	cout << "copy constructor" << endl;
	vector<double>	xd = {1.0, 2.0, 3.0}, yd = {4.0, 5.0, 6.0};
	vector<float>	xf = {1.0, 2.0, 3.0}, yf = {1.0, 2.0, 3.0};
	vektor<double, true>	zd(xd);
	vektor<float, true>		zf(xf);
	vektor<double>			zd2(xd);
	vektor<float>			zf2(xf);

	cout << zd << endl;
	cout << zf << endl;
	cout << zd2 << endl;
	cout << zf2 << endl;

	return;
}

void test2()
{
	cout << "default constructor" << endl;
	volatile vektor<double, true>		xd;
	volatile vektor<float, true>		xf;
	volatile vektor<int, true>			xi;
	volatile vektor<double>				xd2;
	volatile vektor<float>				xf2;
	volatile vektor<int>				xi2;

	return;
}

void test3()
{
	vector<double>	x = {1.0, 2.0, 3.0};
	vector<double>	z = {2.0, 3.0};
	vektor<double, true>	y(x);

	cout << "compare vektor to vector" << endl;
	cout << "y == x is " << (y == x) << endl;
	cout << "compare vector to vektor" << endl;
	cout << "x == y is " << (x == y) << endl;	
	cout << "compare vektor to vector (false)" << endl;
	cout << "y == z is " << (y == z) << endl;
	cout << "comapre vector to vektor (false)" << endl;
	cout << "z == y is " << (z == y) << endl;
	return;
}

void test4()
{
	vector<double>			x = {1.0, 2.0, 3.0};
	vektor<double, true>	z;

	z = x;
	cout << "test assignment" << endl;
	cout << "z = x results in (z == x) = " << (z == x) << endl;
	return;
}

void test5()
{
	vector<double>			x = {1.0, 2.0, 3.0}, y = {2.0, 3.0, 4.0};
	vektor<double>			z1(x), z2(y), z3;

	z3 = z1 + z2;
	cout << "addition: " << z1 << "+" << z2 << "==" << z3 << endl;
	return;
}

void test6()
{
	vector<double>			x = {1.0, 2.0, 3.0}, y = {2.0, 3.0, 4.0}, a = { 20.0 };
	vektor<double, true>	z1(x), z2(y), z3;
 
 	cout << "multiplication test: " << endl;
	z3 = z1 * z2;
	cout << "(z1 * z2 == { 20.0 }) == " << (z3 == a) << endl;
	cout << "z3 is valid == " << z3.isValid() << endl;
	z1 = z2 * z3;
	cout << "z1 = " << z1 << " is valid == (should be false) " << z1.isValid() << endl;

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
	test2();
	test3();
	test4();
	test5();
	test6();

	if((rc = getrusage(RUSAGE_SELF, &ru)) != 0) { perror("getrusage 1");}
	endTime = ru.ru_utime.tv_sec + ru.ru_stime.tv_sec + ((long double)(ru.ru_utime.tv_usec + ru.ru_stime.tv_sec)) / 1000000;
	cout << "Computed " << r << " in " << endTime - startTime << endl;
	return(0);
}