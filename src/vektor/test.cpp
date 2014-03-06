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

void test3()
{
	std::vector<char>	v = { 'a', 'b', 'c'};
	vektor<char>	x(v), y;
	
	cout << "test3" << endl;
	y = x;
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	cout << "end test3" << endl;
	return;

}

void test4()
{
	vektor<char>	x, y;

	cout << "test4" << endl;
	y = x;
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	cout << "end test4" << endl;
	return;

}

void test5()
{
	std::vector<double>	v = {1.0, 2.0, 3.0};
	vektor<double>		x(v), y(v), z;
	cout << "test5" << endl;
	z = x + y;
	cout << "z = " << z << endl;
	cout << "end test5" << endl;
}

void test6()
{
	std::vector<double> v1 = {1.0, 2.3, 4.0};
	std::vector<double> v2 = {2.3, 4.5};
	vektor<double>		x(v1), y(v2), z;
	cout << "test6" << endl;
	z = y + x;
	cout << "z = " << z << endl;
	cout << "end test6" << endl;

}

int main(int argc, char *argv[])
{
	int 		rc;

	cout << "main start" << endl;

	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	
	return(0);
}