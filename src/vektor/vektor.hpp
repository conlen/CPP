#include <iostream>
#include <vector>

template<typename T>
class vektor 
{
	private:
		std::vector<T>	x;
	public:
		vektor();
		vektor(const std::vector<T> &v);
		~vektor();
		vektor<T>& 	operator=(const std::vector<T> &o);
		vektor<T>	operator+(const vektor<T> &o);

	friend std::ostream& operator<<(std::ostream& s, vektor<T> &v) {
		int	i;

		if(v.x.size() > 0) {
			s << "<";
			for(i=0; i<v.x.size() -1; i++) {
				s << v.x[i] << ",";
			}
			s << v.x[i] << ">";
			return s;
		} else {
			s << "<NO_SIZE>";
			return(s);
		}
	}
};

template<typename T>
vektor<T>::vektor()
{
	std::cout << "Construct vektor" << std::endl;
	return;
}


template<typename T>
vektor<T>::vektor(const std::vector<T> &o)
{
	std::cout << "Construct vektor from vector<T>" << std::endl;
	x = o;
	return;
}

template<typename T>
vektor<T>::~vektor()
{
	std::cout << "Destruct vektor" << std::endl;
	return;
}

template<typename T>
vektor<T>& vektor<T>::operator=(const std::vector<T> &o) 
{
	x = o;
	std::cout << "assign vektor" << std::endl;
	return(*this);
}

template <typename T>
vektor<T>	vektor<T>::operator+(const vektor<T> &o)
{
	vektor<T>	r;
	std::vector<T>	y;

	y.resize(x.size());
	for(auto i = 0; i< x.size(); i++) {
		y[i] = x[i] + o.x[i];
	}
	r = y;
	return(r);

}