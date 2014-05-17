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
unique_ptr<vektor<T>[]> gimmeVektor(int count) 
{
	unique_ptr<vektor<T>[]> 	v;

	v = unique_ptr<vektor<T>[]>(new vektor<T>[count]);
	return(v);
}

template<typename T>
void takeVektor(unique_ptr<vektor<T>[]> v) 
{
	return;
}

using namespace std;
int main(int argc, char *argv[]) 
{
	int			count = 0;
	char		copt;	
	unique_ptr<vektor<int>[]>	v;

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
	takeVektor<int>(move(v));
	cout << "bar" << endl;
	return(0);



usage:
	cout << argv[0] << " -n N" << endl;
	return(-1);

}