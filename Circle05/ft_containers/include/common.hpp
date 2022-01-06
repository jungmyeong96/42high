#include "vector.hpp"
#include <vector>
#include <iostream>
#include <string>


template <typename T>
void	printSize(ft::vector<T> const &vector)
{
	ft::vector<T>::const_iterator it = vector.begin();
	ft::vector<T>::const_iterator ite = vector.end();
	std::cout << std::endl << "next content:" << std::endl;
	for (; it != ite; ++it)
		std::cout << "- " << *it << std::endl;

}
