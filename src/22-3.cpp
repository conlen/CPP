#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/stat.h>
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

int main(int argc, char *argv[])
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
	cout << x << endl;
	return(0);
}