#include <vector>
#include <iostream>

using namespace std;


int main(int argc, char *argv[]) 
{
	std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};



	for(auto i : v) {
		cout << i << endl;
	}

	auto i = v.begin();

	cout << *i << endl;
	cout << i[5] << endl;
	cout << *(++i) << endl;


}
