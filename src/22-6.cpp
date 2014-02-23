#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <sys/resource.h>
#include <sys/time.h>

using namespace std;

set<string> inline stringSplit(const string &source, const char *delimiter = " ", bool keepEmpty = false)
{
	set<string>		results;
	size_t			prev = 0, next = 0;

	while ((next = source.find_first_of(delimiter, prev)) != string::npos)
	{
		if (keepEmpty || (next - prev != 0)) results.insert(source.substr(prev, next - prev));
		prev = next + 1;
	}
	if (prev < source.size()) results.insert(source.substr(prev));
	return results;
}

// template the sum function 

template<typename R, class T>
R sum(const T &v) 
{
	R x = 0, i = 0;
	
	for(i=0; i<v.size(); i++) {
		x += v[i];
	}
	return(x);
}

uint64_t inline scoreNames(const set<string> &list)
{
	uint64_t		curScore = 0, i = 0, j = 0, x = 0;
	for(auto k : list) {
		curScore = sum<uint64_t>(k);
		curScore -= ('A' - 1) * k.size();
		x += curScore * (++i);
	}
	return(x);
}

uint64_t computeNameScores()
{
	ifstream		inputFile("names.txt");
	string		s, k, inputNames;
	set<string>	namesList;

	inputFile >> inputNames;
	inputFile.close();
	namesList = stringSplit(inputNames, ",\"");
	return(scoreNames(namesList));	
}

int main(int argc, char *argv[])
{
	uint64_t	x;

	int 		rc;
	struct rusage	ru;
	double			startTime, endTime;
	volatile uint64_t	z;

	if((rc = getrusage(RUSAGE_SELF, &ru)) != 0) { perror("getrusage 1");}
	startTime = ru.ru_utime.tv_sec + ru.ru_stime.tv_sec + ((long double)(ru.ru_utime.tv_usec + ru.ru_stime.tv_sec)) / 1000000;
	x = computeNameScores();
	if((rc = getrusage(RUSAGE_SELF, &ru)) != 0) { perror("getrusage 1");}
	endTime = ru.ru_utime.tv_sec + ru.ru_stime.tv_sec + ((long double)(ru.ru_utime.tv_usec + ru.ru_stime.tv_sec)) / 1000000;
	cout << "Computed " << x << " in " << endTime - startTime << endl;
	return(0);
}