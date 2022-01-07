#include "../include/Vector.hpp"
#include "Vector.hpp"
#include <vector>


template <typename T>
void	printcont(ft::vector<T> const &vector)
{
	typename ft::Vector<T>::const_iterator it = vector.begin();
	typename ft::Vector<T>::const_iterator ite = vector.end();
	std::cout << std::endl << "next content:" << std::endl;
	for (; it != ite; ++it)
		std::cout << "- " << *it << std::endl;
}


int		main(void)
{
	ft::Vector<int> vector(7);
	ft::Vector<int> vector_two(4);
	ft::Vector<int> vector_three;
	ft::Vector<int> vector_four;

	for (unsigned long int i = 0; i < vector.size(); ++i)
		vector[i] = (vector.size() - i) * 3;
	for (unsigned long int i = 0; i < vector_two.size(); ++i)
		vector_two[i] = (vector_two.size() - i) * 5;
	printcont(vector);
	printcont(vector_two);

	vector_three.assign(vector.begin(), vector.end());
	vector.assign(vector_two.begin(), vector_two.end());
	vector_two.assign(2, 42);
	vector_four.assign(4, 21);

	std::cout << "\nAfter assign():" << std::endl;

	printcont(vector);
	printcont(vector_two);
	printcont(vector_three);
	printcont(vector_four);

	vector_four.assign(6, 84);
	printcont(vector_four);

	std::cout << "\n assign() on enough capacity and low size:" << std::endl;

	vector.assign(5, 53);
	vector_two.assign(vector_three.begin(), vector_three.begin() + 3);

	printcont(vector);
	printcont(vector_two);

	{
		std::cout << "vector !"<< std::endl;
	std::vector<int> vector(7);
	std::vector<int> vector_two(4);
	std::vector<int> vector_three;
	std::vector<int> vector_four;

	for (unsigned long int i = 0; i < vector.size(); ++i)
		vector[i] = (vector.size() - i) * 3;
	for (unsigned long int i = 0; i < vector_two.size(); ++i)
		vector_two[i] = (vector_two.size() - i) * 5;
	//printcont(vector);
	//printcont(vector_two);

	vector_three.assign(vector.begin(), vector.end());
	vector.assign(vector_two.begin(), vector_two.end());
	vector_two.assign(2, 42);
	vector_four.assign(4, 21);



	// printcont(vector);
	// printcont(vector_two);
	// printcont(vector_three);
	// printcont(vector_four);

	vector_four.assign(6, 84);
//	printcont(vector_four);

	

	vector.assign(5, 53);
	vector_two.assign(vector_three.begin(), vector_three.begin() + 3);

	// printcont(vector);
	// printcont(vector_two);
	}

	return (0);
}
