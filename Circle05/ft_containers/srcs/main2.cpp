
// #include "Vector.hpp"
// #include <iostream>
// #include <string>
// #include <iterator> //임시


// template< typename T >
// void printele ( const T& t)
// {
// 	 //임시 iterator로 바꿔야함
// 	 if(t.begin())
// 		std::cout<< *(t.begin()) <<std::endl;
// }


// int main()
// {
// 	Vector <int> intarr;
// 	Vector <int> intAarr(10, 3);
// 	Vector <int> intBarr(intAarr);

// 	printele(intarr);
// 	printele(intAarr);	
// 	printele(intBarr);

//     return (0);
// }

#include <iostream>
#include <string>
#include <deque>
// #if 1 //CREATE A REAL STL EXAMPLE
// 	#include <map>
	#include <stack>
 	#include <vector>
// 	namespace ft = std;
//else
//	#include <Map.hpp>
	#include "../include/Vector.hpp"
	#include "../include/Stack.hpp"
//#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::Stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->ctnr = rhs.ctnr;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::Stack<T>::container_type::iterator iterator;

	iterator begin() { return this->ctnr.begin(); }
	iterator end() { return this->ctnr.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::Vector<std::string> vector_str;
	ft::Vector<int> vector_int;
	ft::Stack<int> stack_int;
	ft::Vector<Buffer> vector_buffer;
	std::vector<Buffer> a;
	ft::Stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	//	ft::map<int, int> map_int;
	printf("---------\n");
	for (int i = 0; i < COUNT; i++)
	{
		a.push_back(Buffer());
		vector_buffer.push_back(Buffer());
	}

	printf("---------\n");
	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
		printf("---------\n");
	ft::Vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
			printf("---------\n");
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	// for (int i = 0; i < COUNT; ++i)
	// {
	// 	map_int.insert(ft::make_pair(rand(), rand()));
	// }

	// int sum = 0;
	// for (int i = 0; i < 10000; i++)
	// {
	// 	int access = rand();
	// 	sum += map_int[access];
	// }
	// std::cout << "should be constant with the same seed: " << sum << std::endl;

	// {
	// 	ft::map<int, int> copy = map_int;
	// }
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	// {
	// // 	std::cout << *it;
	// // }
	// // std::cout << std::endl;
	return (0);
}