#include <vector>
#include <typeinfo>

template<typename T, bool debug = false>
class vektor {
	private:
		bool			valid;
		std::vector<T>	x;
	public:
		vektor();
		vektor(const vektor &other);
		vektor(const std::vector<T> &v);
		~vektor();
		vektor &operator=(const vektor &other);
		vektor &operator=(const std::vector<T> &o);
		bool operator==(const std::vector<T> &o);
		vektor operator+(const vektor &o);
		vektor operator*(const vektor &o);
		bool isValid();

	friend std::ostream& operator<<(std::ostream& s, vektor<T, debug> &v) {
		int	i;

		if(debug == true) {
			std::cout << std::endl << "output vector of length " << v.x.size() << " and validity " << v.valid << std::endl;
		}
		if(v.x.size() == 0 && v.valid == true) {
			std::cout << "NO SIZE BUT VALID" << std::endl;
			return s;
		}
		if(v.valid == true) {
			s << "<";
			for(i=0; i<v.x.size() -1; i++) {
				s << v.x[i] << ",";
			}
			s << v.x[i] << ">";
			return s;
		} else {
			s << "<INVALID>";
			return(s);
		}
	}

	friend bool operator==(const std::vector<T> &l, const vektor<T, debug> &r) {
		if(debug == true) std::cout << "test equality vector == vektor" << std::endl;
		return(l == r.x);
	}
};

template<typename T, bool debug>
vektor<T, debug>::vektor() 
	: valid(false)
{ 
	if(debug == true) std::cout << "I made a vektor with " << typeid(x).name()  << std::endl; 
}

template<typename T, bool debug>
vektor<T, debug>::vektor(const vektor &o)
	: x(o.x), valid(o.valid)
{
	if(debug == true) std::cout << "copy constructor with " << typeid(x).name()  << std::endl;
}

template<typename T, bool debug>
vektor<T, debug>::vektor(const std::vector<T> &v) : x(v), valid(false)
{ 
	if(debug == true) std::cout << "assignment operator with " << typeid(x).name()  << std::endl;
}

template<typename T, bool debug>
vektor<T, debug>::~vektor() 
{ 
	if(debug == true) std::cout << "vektor is dead" << std::endl; 
}

template<typename T, bool debug>
vektor<T, debug> &vektor<T, debug>::operator=(const vektor &other)
{
	if(debug == true) std::cout << "vector assignment from vektor" << std::endl;
	x = other.x;
	return(*this);

}

template<typename T, bool debug>
vektor<T, debug> &vektor<T, debug>::operator=(const std::vector<T> &o) 
{
	if(debug == true) std::cout << "assignment from std::vector<T>" << std::endl;
	x = o;
	return(*this);
}

template<typename T, bool debug>
bool vektor<T, debug>::operator==(const std::vector<T> &o)
{
	if(debug == true) std::cout << "test equality" << std::endl;
	return(x == o);
}

template<typename T, bool debug>
vektor<T, debug> vektor<T, debug>::operator+(const vektor &o)
{
	vektor	r;
	std::vector<T>	y;

	if(debug == true) std::cout << "vector addition" << std::endl;
	y.resize(x.size());
	for(auto i=0; i<x.size(); i++) {
		y[i] = x[i] + o.x[i];
	}
	r = y;
	return(r);
}

template<typename T, bool debug>
vektor<T, debug> vektor<T, debug>::operator*(const vektor &o) 
{
	vektor	r;

	if(debug == true) {
		std::cout << "vektor<T, debug>::operator*(const vektor &o)" << std::endl;
		std::cout << "this->x.size() == " << x.size() << std::endl;
		std::cout << "o.x.size() == " << o.x.size() << std::endl;
	}
	if(x.size() != o.x.size()) {
		if(debug == true) {
			std::cout << "invalid dot product" << std::endl;
		}
		r.valid = false; 
		return(r);
	}
	r.valid = true;
	r.x.resize(1);
	r.x[0] = 0;
	for(int i = 0; i<x.size(); i++) {
		r.x[0] += x[i] * o.x[i];
	}
	return(r);
}

template<typename T, bool debug>
bool vektor<T, debug>::isValid() 
{
	if(debug == true) {
		std::cout << "vektor<T, debug>::isValid()" << std::endl;
		std::cout << "valid = " << valid << std::endl;
	}
	return(valid);
}
