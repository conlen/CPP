#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

#include <sys/time.h>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/moment.hpp>


#include "2048.hpp"

using namespace std;
using namespace boost::accumulators;
namespace bacc = boost::accumulators;

#define BUG 0

int main(int argc, char *argv[])
{
	tofe<0>				*t;
	int 				score;
	int 				i, r, rc;
	short unsigned int 	Xi[3];
	struct timeval		time;
	accumulator_set<double, stats<tag::min, tag::max, tag::mean, tag::moment<2> > > acc;

	if((rc = gettimeofday(&time, NULL)) != 0) goto error0;
	memcpy(Xi, &time.tv_usec, sizeof(suseconds_t) < 6 ? sizeof(suseconds_t) : 6);

	for(i=0; i<100000; i++) {
		t = new tofe<0>;
		while(t->movesLeft()) {
			if(BUG == 1) cout << endl << *t << endl;
			r = erand48(Xi) * 4;
			switch(r) {
				case	0 :
					t->move(1);
					if(BUG == 1) cout << "up" << endl;
					break;
				case	1 :
					if(BUG == 1) cout << "down" << endl;
					t->move(-1);
					break;
				case	2 :
					if(BUG == 1) cout << "left" << endl;
					t->move(-2);
					break;
				case	3 :
					if(BUG == 1) cout << "right" << endl;
					t->move(2);
					break;
				default :
					goto error0;
			}
		}
		if(BUG == 1) cout << endl << *t << endl;
		score = t->getScore();
		acc(score);
		if(i % 100 == 0) cout << "run " << i << ", score = " << score << ", min = " << bacc::min(acc) << ", max = " 
		<< bacc::max(acc) << ", mean = " << mean(acc) << ", stdev = " << sqrt(moment<2>(acc)/i) << endl;
		delete t;
	}

	// cout << t << endl;
	// while(t.movesLeft()) {
	// 	cin.get(input);
	// 	switch(input) {
	// 		case	'w' : 
	// 			t.move(1);
	// 			break;
	// 		case	's' : 
	// 			t.move(-1);
	// 			break;
	// 		case	'a' :
	// 			t.move(-2);
	// 			break;
	// 		case	'd' : 
	// 			t.move(2);
	// 			break;
	// 	}
	// 	cout << "about to output t" << endl;
	// 	if(input != 10) cout << endl << t << endl;
	// }
	// cout << endl << t << endl;
	return(0);
error0:
	cout << "I'm sorry Dave, I can't do that" << endl;
	return(-1);
}