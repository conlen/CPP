#include <iomanip>
#include <iostream>
#include <cstdint>
#include <vector>

#include <sys/time.h>

#define TOFE_EXCEPTION	1

template<int DEBUG = 0>
class tofe;

template<int DEBUG = 0>
std::ostream& operator<<(std::ostream& s, const tofe<DEBUG> &t);

template<int DEBUG>
class tofe
{
	private:
		std::vector<std::vector<int>>	board;
		unsigned long 					score = 0;
		short unsigned int				Xi[3];

		bool test1();
	public:
		tofe();
		~tofe();

		void move(int dimension);
		bool movesLeft();
		unsigned long getScore() const;
		bool runTests();

	friend std::ostream& operator<< <DEBUG>(std::ostream& s, const tofe<DEBUG> &t);
};

template<int DEBUG>
tofe<DEBUG>::tofe()
{
	int 			i, j, rc, location[2], values[2];
	struct timeval	t;

/* initialize board */
	board.resize(5);
	for(i=0; i<5; i++) {
		board[i].resize(5);
		for(j=0; j<5; j++) {
			board[i][j] = 0;
		}
	}

/* initialize rng */
	if((rc = gettimeofday(&t, NULL)) != 0) goto error0;
	memcpy(Xi, &t.tv_usec, sizeof(suseconds_t) < 6 ? sizeof(suseconds_t) : 6);

/* place first two pieces */
	location[0] = erand48(Xi) * 25;
	do {
		location[1] = erand48(Xi) * 25;
	} while(location[0] == location[1]);
	values[0] = ((int)(erand48(Xi) * 10) == 0) ? 4 : 2;
	values[1] = ((int)(erand48(Xi) * 10) == 0) ? 4 : 2;

	board[location[0]/5][location[0]%5] = values[0];
	board[location[1]/5][location[1]%5] = values[1];
	return;
error0:
	throw(TOFE_EXCEPTION);
	return;

}

template<int DEBUG>
tofe<DEBUG>::~tofe()
{
	return;
}

/*
	dimension indicates which dimension moves, 1 indexed
		positive dimension moves the pieces in the positive direction
		negative dimension moves the pieces in the negative direction
*/

template<int DEBUG>
int collapse(int v[5])
{
	int j, k, score = 0;
	if(DEBUG == 1) std::cout << "vector = <" << v[0] << "," << v[1] << "," << v[2] << ","
	<< v[3] << "," << v[4] << "> -> ";
	for(j=0; j<4; j++) {
		if(v[j] != v[j+1]) continue;
		v[j] *= 2;
		score += v[j];
		for(k=j+1; k<4; k++) {
			v[k] = v[k+1];
		}
		v[4] = 0;		
	}
	if(DEBUG == 1) std::cout << "<" << v[0] << "," << v[1] << "," << v[2] << ","
	<< v[3] << "," << v[4] << ">" << std::endl;
	return(score);
}

template<int DEBUG>
void tofe<DEBUG>::move(int dimension)
{
	int 	i, j, k, cursor = 0, update = 0;
	int 	newVector[5] = {0, 0, 0, 0, 0};
	int 	location;

	if(dimension == 1) {
		for(i=0; i<5; i++) {
			cursor = 0;
			for(j=0; j<5; j++) newVector[j] = 0;
			for(j=0; j<5; j++) {
				if(board[i][j] == 0) continue;
				newVector[cursor++] = board[i][j];
			}	
			score += collapse<DEBUG>(newVector);	
			for(j=0; j<5; j++) { 
				if(board[i][j] != newVector[j]) update = 1;
				board[i][j] = newVector[j]; 
			}
		}
	}

	if(dimension == -1) {
		for(i=0; i<5; i++) {
			cursor = 0;
			for(j=0; j<5; j++) newVector[j] = 0;
			for(j=4; j>=0; j--) {
				if(board[i][j] == 0) continue;
				newVector[cursor++] = board[i][j];
			}
			score += collapse<DEBUG>(newVector);	
			for(j=0; j<5; j++) {
				if(board[i][j] != newVector[4-j]) update = 1;
				board[i][j] = newVector[4-j];
			}
		}
	}

	if(dimension == 2) {
		for(i=0; i<5; i++) {
			cursor = 0;
			for(j=0; j<5; j++) newVector[j] = 0;
			for(j=4; j>=0; j--) {
				if(board[j][i] == 0) continue;
				newVector[cursor++] = board[j][i];
			}	
			score += collapse<DEBUG>(newVector);
			for(j=0; j<5; j++) {
				if(board[j][i] != newVector[4-j]) update = 1;
				board[j][i] = newVector[4-j];
			}
		}					
	}

	if(dimension == -2) {
		for(i=0; i<5; i++) {
			cursor = 0;
			for(j=0; j<5; j++) newVector[j] = 0;
			for(j=0; j<5; j++) {
				if(board[j][i] == 0) continue;
				newVector[cursor++] = board[j][i];
			}				
			score += collapse<DEBUG>(newVector);
			for(j=0; j<5; j++) { 
				if(board[j][i] != newVector[j]) update = 1;
				board[j][i] = newVector[j]; 
			}	
		}					
	}

	if(DEBUG == 1) std::cout << "adding the new piece" << std::endl;

/* only add a new pice if we updated the board */
	if(update) {
		for(i=0; i<5; i++) {
			for(j=0; j<5; j++) {
				if(board[i][j] == 0) break;
			}
			if(board[i][j] == 0) break;
		}
		if(i<5 && j < 5) {
			while(1) {
				location = erand48(Xi) * 25;
				if(DEBUG == 1)
					std::cout << "location[" << location/5 <<  "][" << location%5 << "] = " 
					<< board[location/5][location%5] << std::endl;
				if(board[location/5][location%5] != 0) continue;
				board[location/5][location%5] = (int)((erand48(Xi) * 10) == 0) ? 4 : 2;
				break;
			}
		}
	}
	if(DEBUG == 1) std::cout << "done adding piece" << std::endl;
	return;
}

template<int DEBUG>
bool tofe<DEBUG>::movesLeft()
{
	int 	i, j;

	if(DEBUG == 1) std::cout << "movesLeft()" << std::endl;
	for(i=0; i<5; i++) {
		for(j=0; j<5; j++) {
			if(board[i][j] == 0) return(true);
		}
	}
	for(i=0; i<4; i++) {
		for(j=0; j<5; j++) {
			if(board[i][j] == board[i+1][j]) return(true);
		}
	}
	for(i=0; i<5; i++) {
		for(j=0; j<4; j++) {
			if(board[i][j] == board[i][j+1]) return(true);
		}
	}
	return(false);
}

template<int DEBUG>
unsigned long tofe<DEBUG>::getScore() const
{
	return(score);
}

template<int DEBUG>
bool tofe<DEBUG>::runTests() 
{
	bool	pass = true;

	return(this->test1());
}

/*
	The following board triggered movesLeft() == false but up/down should be an option. 

       2      16       2       8       2
       2       8    1024     128      16
       8       2      16     256     512
      64      32       8      16       8
       4       8       4       2       4

*/
template<int DEBUG>
bool tofe<DEBUG>::test1()
{
	board[0][0] = 2;
	board[0][1] = 2;
	board[0][2] = 8;
	board[0][3] = 64;
	board[0][4] = 4;

	board[1][0] = 16;
	board[1][1] = 8;
	board[1][2] = 2;
	board[1][3] = 32;
	board[1][4] = 8;

	board[2][0] = 2;
	board[2][1] = 1024;
	board[2][2] = 16;
	board[2][3] = 8;
	board[2][4] = 4;

	board[3][0] = 8;
	board[3][1] = 128;
	board[3][2] = 256;
	board[3][3] = 16;
	board[3][4] = 2;

	board[4][0] = 2;
	board[4][1] = 16;
	board[4][2] = 512;
	board[4][3] = 8;
	board[4][4] = 4;

	std::cout << *this << std::endl;
	return(this->movesLeft());
}

template<int DEBUG>
std::ostream& operator<<(std::ostream& s, const tofe<DEBUG> &t) {
	int 	i, j;

	if(DEBUG == 1) std::cout << "output of t" << std::endl;
	s << "score: " << std::setw(12) << t.score << std::endl;
	for(i=0; i<5; i++) {
		for(j=0; j<5; j++) {
			s << std::setw(8) << t.board[j][i];
		}
		s << std::endl;
	}
	return s;
}
