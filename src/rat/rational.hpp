#include <iostream>

template<typename T, bool DEBUG>
class rational;

template<typename T, bool DEBUG>
std::ostream& operator<<(std::ostream& s, rational<T, DEBUG> &r);

template<typename T, bool DEBUG=false>
class rational {
	private:
		T 	n, d;
	public:
								rational();
								rational(T numerator, T denominator);
								rational(T value);
								~rational();
		rational<T, DEBUG>&		operator=(const rational<T, DEBUG> &o);
		bool					operator==(const rational<T, DEBUG> &o);
		rational<T, DEBUG>		operator+(const rational<T, DEBUG> &o);
		rational<T, DEBUG>		operator-(const rational<T, DEBUG> &o);		
		rational<T, DEBUG>		operator*(const rational<T, DEBUG> &o);
		rational<T, DEBUG>		operator/(const rational<T, DEBUG> &o);
		template<typename U>
		rational<T, DEBUG>		operator*(const U &o);
		void					reduce();
	friend std::ostream& operator<< <T, DEBUG>(std::ostream& s, rational<T, DEBUG> &r);
};

template<typename T, bool DEBUG> template<typename U>
rational<T, DEBUG> rational<T, DEBUG>::operator*(const U &o)
{
	rational<T, DEBUG> r;
	r.n = o*n;
	r.d = d;
	return(r);
}

template<typename T, bool DEBUG>
rational<T, DEBUG>::rational()
	: n(0), d(1)
{
	return;
}

template<typename T, bool DEBUG>
rational<T, DEBUG>::rational(T numerator, T denominator)
	: n(numerator), d(denominator)
{
	this->reduce();
	return;
}

template<typename T, bool DEBUG>
rational<T, DEBUG>::rational(T value)
	: n(value), d(1)
{
	return;
}

template<typename T, bool DEBUG>
rational<T, DEBUG>::~rational()
{
	return;
}

template<typename T, bool DEBUG>
rational<T, DEBUG> rational<T, DEBUG>::operator+(const rational<T, DEBUG> &o)
{
	rational<T, DEBUG>	r;
	r.n = n * o.d + o.n * d;
	r.d = d * o.d;
	return(r);
}

template<typename T, bool DEBUG>
rational<T, DEBUG> rational<T, DEBUG>::operator-(const rational<T, DEBUG> &o)
{
	rational<T, DEBUG>	r;
	r.n = n * o.d - o.n * d;
	r.d = d * o.d;
	r.reduce();
	return(r);
}

template<typename T, bool DEBUG>
rational<T, DEBUG> rational<T, DEBUG>::operator*(const rational<T, DEBUG> &o)
{
	rational<T, DEBUG>	r;
	r.n = n * o.n;
	r.d = d * o.d;
	r.reduce();
	return(r);
}

template<typename T, bool DEBUG>
rational<T, DEBUG> rational<T, DEBUG>::operator/(const rational<T, DEBUG> &o)
{
	rational<T, DEBUG>	r;
	r.n = n * o.d;
	r.d = d * o.n;
	r.reduce();
	return(r);
}

template<typename T, bool DEBUG>
rational<T, DEBUG>& rational<T, DEBUG>::operator=(const rational<T, DEBUG> &o)
{
	n = o.n; d = o.d;
	this->reduce();
	return(*this);
}

template<typename T, bool DEBUG>
bool rational<T, DEBUG>::operator==(const rational<T, DEBUG> &o)
{
	return(d == o.d && n == o.n);
}

template<typename T, bool DEBUG>
void rational<T, DEBUG>::reduce()
{
	T 	t, a, b;

// Euclidean algorithm 
	a = n; b = d;
	while(b != 0) {
		t = b;
		b = a % b;
		a = t;
	}
// a = gcd(n, d)

	n = n / a;
	d = d / a;
	return;

}

template<typename T, bool DEBUG>
std::ostream& operator<<(std::ostream& s, rational<T, DEBUG> &r)
{
	return s << r.n << "/" << r.d << " ";
}