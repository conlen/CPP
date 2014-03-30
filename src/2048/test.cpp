#include <cstdint>
#include <cstring>
#include <iostream>

#include "2048.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	tofe<1>	t;
	char	input;

	cout << t << endl;
	while(t.movesLeft()) {
		cin.get(input);
		switch(input) {
			case	'w' : 
				t.move(1);
				break;
			case	's' : 
				t.move(-1);
				break;
			case	'a' :
				t.move(-2);
				break;
			case	'd' : 
				t.move(2);
				break;
		}
		cout << "about to output t" << endl;
		if(input != 10) cout << endl << t << endl;
	}
	cout << endl << t << endl;
	return(0);
}