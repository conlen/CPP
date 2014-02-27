#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <sys/resource.h>
#include <sys/time.h>

using namespace std;


class vektor {
	private:
		vector<double>	x;
	public:
		vektor();
		~vektor();
		vektor &operator=(const vektor &other);
		vektor &operator=(const vector<double> &other);
		vektor operator+(const vektor &other);
		vector<double> get_x();
		void set_x(vector<double> &other);

	friend std::ostream& operator<<(std::ostream& s, vektor &v) {
		
		for(auto k : v.x) {
			s << k << ",";
		}

		return s;
	}
};

vektor::vektor() { cout << "I made a vektor" << endl; }
vektor::~vektor() { cout << "vektor is dead" << endl; };
// vektor &vektor::operator=(const vektor &other) 
// {
// 	cout << "assignment" << endl;
// 	x = other;
// 	return(*this);
// }

vektor &vektor::operator=(const vektor &other)
{
	x = other.x;
	return(*this);

}
vektor &vektor::operator=(const vector<double> &other) 
{
	cout << "assignment from vector<double>" << endl;
	x = other;
	return(*this);
}

vektor vektor::operator+(const vektor &other){
	vektor	r;
	vector<double>	y;

	y.resize(x.size());
	for(auto i=0; i<x.size(); i++) {
		y[i] = x[i] + other.x[i];
	}
	r = y;
	return(r);
}

vector<double> vektor::get_x()
{
	return(x);
}

void vektor::set_x(vector<double> &other)
{
	cout << "do something when someone sets x" << endl;
	x = other;
	return;
}

int main(int argc, char *argv[])
{
	int 		rc;
	struct rusage	ru;
	double			startTime, endTime;
	vector<double> 	x = {1.0, 2.0, 3.0}, y = {4.0, 5.0, 6.0};
	vector<float>	x2 = {11.0, 2.0, 3.0}, y2 = {41.0, 5.0, 6.0};
	double 			r;
	vektor			z, z2, z3;


	cout << "main start" << endl;
	if((rc = getrusage(RUSAGE_SELF, &ru)) != 0) { perror("getrusage 1");}
	startTime = ru.ru_utime.tv_sec + ru.ru_stime.tv_sec + ((long double)(ru.ru_utime.tv_usec + ru.ru_stime.tv_sec)) / 1000000;

	z = x;
	cout << z << endl;

	z2 = z;
	cout << z2 << endl;

	z3 = z + z2;
	cout << z3 << endl;

	z3.set_x(y);
	cout << z3 << endl;
	if((rc = getrusage(RUSAGE_SELF, &ru)) != 0) { perror("getrusage 1");}
	endTime = ru.ru_utime.tv_sec + ru.ru_stime.tv_sec + ((long double)(ru.ru_utime.tv_usec + ru.ru_stime.tv_sec)) / 1000000;
	cout << "Computed " << r << " in " << endTime - startTime << endl;
	return(0);
}