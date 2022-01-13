#ifndef PAIR_HPP
# define PAIR_HPP


namespace ft
{
	template < class T1, class T2>
	struct pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;

		first_type	first;
		second_type	second;

		pair(void): first(), second() {}
		pair(first_type const & x, second_type const & y) :first(x), second(y) {}

		template< class U1, class U2 >
		pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {}

		pair & operator=(pair<T1, T2> const & rhs)
		{
			if (this != &rhs)
			{
				this->first = rhs.first;
				this->second = rhs.second;
			}
			return *this;
		}
	};

	template < class T1, class T2>
	pair<T1, T2>	make_pair(T1 k, T2 d)
	{
		return pair<T1, T2>(k, d);
	}

/*
				*		Lexicograpphical comparison operators
*/

	template < class T1, class T2>
	bool	operator==(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template < class T1, class T2>
	bool	operator!=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{
		return !(lhs == rhs);
	}

	template < class T1, class T2>
	bool	operator<(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{
		return ((lhs.first < rhs.first || (!(rhs.first < lhs.first)))
				&& (lhs.second < rhs.second || (!(rhs.second < lhs.second))));
	}

	template < class T1, class T2>
	bool	operator<=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{
		return !(rhs < lhs);
	}

	template < class T1, class T2>
	bool	operator>(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{
		return rhs < lhs;
	}

	template < class T1, class T2>
	bool	operator>=(pair<T1, T2> const & lhs, pair<T1, T2> const & rhs)
	{
		return !(lhs < rhs);
	}


}
#endif