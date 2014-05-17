#include <iomanip>
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <memory>

#include <unistd.h>

#include "vektor/vektor.hpp"

using namespace std;


template<typename T>
shared_ptr<vektor<T>> gimmeVektor(int count) 
{
	shared_ptr<vektor<T>> 	v;

	v = shared_ptr<vektor<T>>(new vektor<T>[count], default_delete<vektor<T>[]>());
	return(v);
}

template<typename T>
void takeVektor(shared_ptr<vektor<T>> v) 
{
	return;
}

using namespace std;
int main(int argc, char *argv[]) 
{
	int			count = 0;
	char		copt;	
	shared_ptr<vektor<int>>	v;

	while((copt = getopt(argc, argv, "n:")) != -1) {
		switch(copt) {
			case	'n':
				count = atoi(optarg);
				break;
			default:
				goto usage;
		}
	}
	if(count == 0) goto usage;	
	cout << "count = " << count << endl;
	v = gimmeVektor<int>(count);
	cout << "foo" << endl;
	takeVektor<int>(v);
	cout << "bar" << endl;
	return(0);



usage:
	cout << argv[0] << " -n N" << endl;
	return(-1);

}