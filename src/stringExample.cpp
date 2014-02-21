#include <iostream>
#include <string>

using namespace std;


int main(int argc, char *argv[])
{
	char foo[] = "bar";
	string s3;

	s3 = foo;
	foo[0] = 'c';

	cout << s3 << " = " << foo << endl;
	return(0);
}