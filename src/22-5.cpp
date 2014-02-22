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

uint64_t sum(const string &list) 
{
	uint64_t x = 0;
	uint64_t i = 0;
	for(i=0; i<list.size(); i++) {
		x += list[i];
	}
	return(x);
}

uint64_t inline scoreNames(const set<string> &list)
{
	uint64_t		curScore = 0, i = 0, j = 0, x = 0;
	for(auto k : list) {
		curScore = sum(k);
		curScore -= ('A' - 1) * k.size();
		x += curScore * (++i);
	}
	return(x);
}

int main(int argc, char *argv[])
{
	ifstream		inputFile("names.txt");
	string		s, k, inputNames;
	set<string>	namesList;

	inputFile >> inputNames;
	inputFile.close();
	namesList = stringSplit(inputNames, ",\"");
	cout << scoreNames(namesList) << endl;
	return(0);
}