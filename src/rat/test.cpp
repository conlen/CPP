#include <iostream>
#include "rational.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	rational<int>	x(1, 2), y(1, 3), z, r(4, 20);
	int				c = 4;
	cout << x << endl;
	cout << y << endl;
	z = x+y;
	cout << z << endl;
	z = x*y;
	cout << z << endl;
	cout << (x == y) << " should be false" << endl;
	cout << (x == x) << " should be true" << endl;
	cout << r << endl;
	z = x*4;
	cout << z << endl;
	return(0);
}