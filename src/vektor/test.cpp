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
	z = x + y;
	cout << "z = " << z << endl;
	cout << "end test6" << endl;

}

void test7()
{
	std::vector<double> v1 = {1.0, 2.0, 3.0};
	std::vector<double> v2 = {4.0, 5.0, 6.0};
	vektor<double>		x(v1), y(v2), z;

	cout << "test7" << endl;
	z = x * y;
	cout << "z = " << z << endl;
	cout << "end test7" << endl;
}

void test8()
{
	std::vector<double> v1 = {1.0, 2.0, 3.0};
	double				a = 10;
	vektor<double>		x(v1), z;

	cout << "test8" << endl;
	z = a * x;
	cout << "x = " << x << endl;
	cout << "z = " << z << endl;
	z = x * a;
	cout << "x = " << x << endl;
	cout << "z = " << z << endl;
	cout << "end test8" << endl;
}

void test9()
{
	std::vector<double> v1 = {1.0, 2.3, 4.0};
	std::vector<double> v2 = {1.0, 2.0, 3.0};
	vektor<double>		x(v1), y(v2), z;

	cout << "test9" << endl;
	z = x - y;
	cout << "z = " << z << endl;
	cout << "end test9" << endl;	
}

void test10()
{
	std::vector<double>	v1 = {1.0, 2.0, 3.0};
	vektor<double>		x(v1);

	cout << "test10" << endl;
	cout << "x.dimension() = " << x.dimension() << endl;
	cout << "x.isValid() = " << x.isValid() << endl;
	cout << "end test10" << endl;
}

void test11()
{
		std::vector<float>	v1 = {1.2, 3.4, 5.6};
		vektor<float>		x(v1);
		vektor<int>			y;	

		cout << "test11" << endl;
		y = x;
		cout << "y = " << y << endl;
		cout << "end test11" << endl;

}

void test12()
{
	std::vector<float>	v1 = {1.2, 3.4, 5.6};
	vektor<float>		x(v1);

	cout << "test12" << endl;
	for(auto i : x) {
		cout << i << endl;
	}
	cout << "end test12" << endl;
}

void test13()
{
	std::vector<float>	v1 = {1.2, 3.4, 5.6};
	vektor<float>		x(v1);

	cout << "test13" << endl;
	
	auto i = x.begin();

	cout << "i[1] = " << i[1] << endl;

	cout << "end test13" << endl;
}


void test14()
{
	std::vector<float>	v1 = {1.2, 3.4, 5.6};
	vektor<float>		x(v1);

	cout << "test14" << endl;
	
	auto i = x.begin();
	i += 2;
	cout << "i = " << *i << endl;

	cout << "end test14" << endl;
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
	test7();
	test8();
	test9();
	test10();
	test11();
	test12();
	test13();
	test14();

	return(0);
}