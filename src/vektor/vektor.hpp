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