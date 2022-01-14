#include "Map.hpp"
#include <utility>

template < class C >
void	inside(const C& c)
{
	//	std::cout << "2" << std::endl;
	typename C::const_iterator it(c.begin());
	typename C::const_iterator ite(c.end());

	while (it != ite)
	{
		std::cout << " |" << (*(it++)).first;
	}
	std::cout << std::endl;
}

template < class FT, class STD >
void	content(const FT & ft_c, const STD & std_c)
{
	std::cout << "____________________________________________" << std::endl << std::endl
		<< "ft	:	" << std::endl;
	//std::cout << "1" << std::endl;
	inside(ft_c);
	std::cout << "____________________________________________" << std::endl << std::endl
		<< "std	:	" << std::endl;
	inside(std_c);
	std::cout << "____________________________________________" << std::endl << std::endl;
}

int main()
{
    ft::Map<char, int> test;
    ft::pair<char, int> a;
    ft::pair<char, int> b;
    ft::pair<char, int> c;
    ft::pair<char, int> d;
    ft::pair<char, int> e;

    a.first = 'a';
    a.second = 30;
    b.first = 'b';
    b.second = 40;
    c.first = 'c';
    c.second = 40;
    d.first = 'd';
    d.second = 40;
    e.first = 'e';
    e.second = 40;
    test['a'];
    test.insert(b);
    test.insert(c);
    test.insert(d);
    test.insert(e);
    test.insert(e);

    test.insert(e);
    test.erase(b.first);
    test['b'];
    test['f'];
    std::cout << test.size() << std::endl ;
    std::cout << test.max_size() << std::endl ;
    std::cout << test.count('a') << std::endl ;

    inside(test);
    return (0);
}