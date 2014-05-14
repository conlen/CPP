#include <iomanip>
#include <iostream>
#include <cstdint>
#include <vector>

#include <sys/time.h>

#define TOFE_EXCEPTION	1


template<int THROW = 0, int DEBUG = 0>
class tofe
{
	private:
		std::vector<std::vector<int>>	board;
		unsigned long 					score = 0;
		short unsigned int				Xi[3];
		std::vector<std::vector<std::vector<int>> *>	history;

		bool test1();
	public:
		tofe();
		~tofe();

		void move(int dimension);
		bool movesLeft();
		unsigned long getScore() const;
		bool runTests();

	friend std::ostream& operator<<(std::ostream& s, const tofe<THROW, DEBUG> &t) {
		int 	i, j;

		if(DEBUG == 1) std::cout << "output of t" << std::endl;
		s << "score: " << std::setw(12) << t.score << std::endl;
		for(i=0; i<4; i++) {
			for(j=0; j<4; j++) {
				s << std::setw(8) << t.board[j][i];
			}
			s << std::endl;
		}
		return s;
	}
};

template<int THROW, int DEBUG>
tofe<THROW, DEBUG>::tofe()
{
	int 			i, j, rc, location[2], values[2];
	struct timeval	t;
	std::vector<std::vector<int>>	*save;

/* initialize board */
	board.resize(4);
	for(i=0; i<4; i++) {
		board[i].resize(4);
		for(j=0; j<4; j++) {
			board[i][j] = 0;
		}
	}

/* initialize rng */
	if((rc = gettimeofday(&t, NULL)) != 0) goto error0;
	memcpy(Xi, &t.tv_usec, sizeof(suseconds_t) < 6 ? sizeof(suseconds_t) : 6);

/* place first two pieces */
	location[0] = erand48(Xi) * 16;
	do {
		location[1] = erand48(Xi) * 16;
	} while(location[0] == location[1]);
	values[0] = ((int)(erand48(Xi) * 10) == 0) ? 4 : 2;
	values[1] = ((int)(erand48(Xi) * 10) == 0) ? 4 : 2;

	board[location[0]/4][location[0]%4] = values[0];
	board[location[1]/4][location[1]%4] = values[1];

	try {
		save = new std::vector<std::vector<int>>;
	}
	catch(std::bad_alloc &ba) {
		std::cerr << "bad_alloc caught: " << ba.what() << std::endl;
		goto error0;
	}
	*save = board;
	history.push_back(save);
	return;
error0:
	if(THROW) throw(TOFE_EXCEPTION);
	return;

}

template<int THROW, int DEBUG>
tofe<THROW, DEBUG>::~tofe()
{
	for(auto i : history) delete i;
	return;
}

/*
	dimension indicates which dimension moves, 1 indexed
		positive dimension moves the pieces in the positive direction
		negative dimension moves the pieces in the negative direction
*/

template<int THROW, int DEBUG>
int collapse(int v[4])
{
	int j, k, score = 0;
	if(DEBUG == 1) std::cout << "collapse()" << std::endl;
	if(DEBUG == 1) std::cout << "vector = <" << v[0] << "," << v[1] << "," << v[2] << ","
	<< v[3] << "," << "> -> ";
	for(j=0; j<3; j++) {
		if(v[j] != v[j+1]) continue;
		v[j] *= 2;
		score += v[j];
		for(k=j+1; k<3; k++) {
			v[k] = v[k+1];
		}
		v[3] = 0;		
	}
	if(DEBUG == 1) std::cout << "<" << v[0] << "," << v[1] << "," << v[2] << ","
	<< v[3] << "," << ">" << std::endl;
	return(score);
}

template<int THROW, int DEBUG>
void tofe<THROW, DEBUG>::move(int dimension)
{
	int 	i, j, k, cursor = 0, update = 0;
	int 	newVector[4] = {0, 0, 0, 0};
	int 	location;
	std::vector<std::vector<int>>	*save;

	if(DEBUG == 1) std::cout << "tofe<THROW, DEBUG>::move()" << std::endl;
	if(dimension == 1) {
		for(i=0; i<4; i++) {
			cursor = 0;
			for(j=0; j<4; j++) newVector[j] = 0;
			for(j=0; j<4; j++) {
				if(board[i][j] == 0) continue;
				newVector[cursor++] = board[i][j];
			}	
			score += collapse<THROW, DEBUG>(newVector);	
			for(j=0; j<4; j++) { 
				if(board[i][j] != newVector[j]) update = 1;
				board[i][j] = newVector[j]; 
			}
		}
	}

	if(dimension == -1) {
		for(i=0; i<4; i++) {
			cursor = 0;
			for(j=0; j<4; j++) newVector[j] = 0;
			for(j=3; j>=0; j--) {
				if(board[i][j] == 0) continue;
				newVector[cursor++] = board[i][j];
			}
			score += collapse<THROW, DEBUG>(newVector);	
			for(j=0; j<4; j++) {
				if(board[i][j] != newVector[3-j]) update = 1;
				board[i][j] = newVector[3-j];
			}
		}
	}

	if(dimension == 2) {
		if(DEBUG == 1) std::cout << "dimension = 2" << std::endl;
		for(i=0; i<4; i++) {
			cursor = 0;
			for(j=0; j<4; j++) newVector[j] = 0;
			if(DEBUG) std::cout << "setting newVector[]" << std::endl;
			for(j=3; j>=0; j--) {
				if(board[j][i] == 0) continue;
				newVector[cursor++] = board[j][i];
			}	
			if(DEBUG) std::cout << "collapsing vector" << std::endl;
			score += collapse<THROW, DEBUG>(newVector);
			for(j=0; j<4; j++) {
				if(board[j][i] != newVector[3-j]) update = 1;
				board[j][i] = newVector[3-j];
			}
		}					
	}

	if(dimension == -2) {
		for(i=0; i<4; i++) {
			cursor = 0;
			for(j=0; j<4; j++) newVector[j] = 0;
			for(j=0; j<4; j++) {
				if(board[j][i] == 0) continue;
				newVector[cursor++] = board[j][i];
			}				
			score += collapse<THROW, DEBUG>(newVector);
			for(j=0; j<4; j++) { 
				if(board[j][i] != newVector[j]) update = 1;
				board[j][i] = newVector[j]; 
			}	
		}					
	}

	if(DEBUG == 1) std::cout << "adding the new piece" << std::endl;

/* only add a new pice if we updated the board */
	if(update) {
		for(i=0; i<4; i++) {
			for(j=0; j<4; j++) {
				if(board[i][j] == 0) break;
			}
			if(board[i][j] == 0) break;
		}
		if(i<4 && j < 4) {
			while(1) {
				location = erand48(Xi) * 16;
				if(DEBUG == 1)
					std::cout << "location[" << location/4 <<  "][" << location%4 << "] = " 
					<< board[location/4][location%4] << std::endl;
				if(board[location/4][location%4] != 0) continue;
				board[location/4][location%4] = (int)((erand48(Xi) * 10) == 0) ? 4 : 2;
				break;
			}
		}
	}
	if(DEBUG == 1) std::cout << "done adding piece" << std::endl;
	try {
		save = new std::vector<std::vector<int>>;
	}
	catch(std::bad_alloc &ba) {
		std::cerr << "bad_alloc caught: " << ba.what() << std::endl;
		goto error0;
	}
	*save = board;
	history.push_back(save);
	return;
error0:
	if(THROW) throw(TOFE_EXCEPTION);
	return;
}

template<int THROW, int DEBUG>
bool tofe<THROW, DEBUG>::movesLeft()
{
	int 	i, j;

	if(DEBUG == 1) std::cout << "movesLeft()" << std::endl;
	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			if(board[i][j] == 0) return(true);
		}
	}
	for(i=0; i<3; i++) {
		for(j=0; j<4; j++) {
			if(board[i][j] == board[i+1][j]) return(true);
		}
	}
	for(i=0; i<4; i++) {
		for(j=0; j<3; j++) {
			if(board[i][j] == board[i][j+1]) return(true);
		}
	}
	return(false);
}

template<int THROW, int DEBUG>
unsigned long tofe<THROW, DEBUG>::getScore() const
{
	return(score);
}

template<int THROW, int DEBUG>
bool tofe<THROW, DEBUG>::runTests() 
{
	bool	pass = true;

	return(this->test1());
}


template<int THROW, int DEBUG>
bool tofe<THROW, DEBUG>::test1()
{

	return(true);
}


