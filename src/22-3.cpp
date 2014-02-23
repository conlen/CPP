#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

priority_queue<string> inline stringSplit(const string &source, const char *delimiter = " ", bool keepEmpty = false)
{
	priority_queue<string>		results;
	size_t						prev = 0, next = 0;

	while ((next = source.find_first_of(delimiter, prev)) != string::npos)
	{
		if (keepEmpty || (next - prev != 0)) results.push(source.substr(prev, next - prev));
		prev = next + 1;
	}
	if (prev < source.size()) results.push(source.substr(prev));
	return results;
}

// C++ version using a priority_queue<string> since it doesn't need sort
uint64_t computeNameScores() 
{
	char 					*d, *cur, *next;
	uint64_t				i = 0, j, curScore = 0, x = 0, qNames;

	ifstream				inputFile("names.txt");
	string					s, k, inputNames;
	priority_queue<string>	namesList;

	inputFile >> inputNames;
	inputFile.close();

	d = (char *)malloc(sizeof(char)*inputNames.length() + 1);
	memcpy(d, inputNames.c_str(), inputNames.length() + 1);
	namesList = stringSplit(inputNames, ",\"");
	qNames = namesList.size();
	while(namesList.size() != 0) {
		k = namesList.top();
		curScore = 0;
		for(j=0; j<k.length(); j++) {
			curScore += k[j] - 'A' + 1;
		}	
		x += curScore * (qNames - ++i + 1);
		namesList.pop();
	}
	return(x);
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