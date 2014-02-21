#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

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

int main(int argc, char *argv[])
{
	char 					*d, *cur, *next;
	uint64_t				i = 0, j, curScore = 0, x = 0, qNames;

	ifstream				inputFile("names.txt");
	string					s, k, inputNames;
	set<string>	namesList;

	inputFile >> inputNames;
	inputFile.close();

	d = (char *)malloc(sizeof(char)*inputNames.length() + 1);
	inputNames.copy(d, inputNames.length());
	namesList = stringSplit(inputNames, ",\"");
	for(auto k : namesList) {
		curScore = 0;
		for(j=0; j<k.length(); j++) {
			curScore += k[j] - 'A' + 1;
		}	
		x += curScore * (++i);
	}
	cout << x << endl;
	return(0);
}