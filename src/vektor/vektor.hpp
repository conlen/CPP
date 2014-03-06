#include <iostream>
#include <vector>

template<typename T>
class vektor 
{
	private:
		std::vector<T>	x;
	public:
		vektor();
		~vektor();
		vektor&		operator=(const std::vector<T> &o);
};

template<typename T>
vektor<T>::vektor()
{
	std::cout << "Construct vektor" << std::endl;
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
	vektor<T>	r;

	std::cout << "assign vektor" << std::endl;
	return(*this);
}