#ifndef PAIR_HPP
# define PAIR_HPP


namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        public:
            typedef T1  first_type;
            typedef T2  second_type;

            first_type  first;
            second_type second;

            pair() : first(), second() {};
            pair (const first_type& a, const second_type& b) : first(a), second(b) {};
            template<class U1, class U2>
            pair (const pair<U1,U2>& pr) : first(pr.first), second(pr.second) {};
            template<class U1, class U2>
            pair (pair<U1, U2>&& pr) : first(std::forward<U1>(pr.first)), second(std::forward<U2>(pr.second)) {};
            ~pair() = default;


        pair& operator= (const pair& pr)
        {
            if (this != &pr)
            {
                first = pr.first;
                second = pr.second;
            }
            return (*this);
        };
        
        Pair& operator=(Pair&& pr)
        {
            if (this != &pr)
            {
                first = std::move(pr.first);
                second = std::move(pr.second);
                return *this;
            }
        }
        
        template<typename U1, typename U2>
        Pair& operator=(const Pair<U1, U2>& pr)
        {
            if (this != &pr)
            {
                first = pr.first;
                second = pr.second;
                return *this;
            }
        }

        template<typename U1, typename U2>
        Pair& operator=(Pair<U1, U2>&& pr)
        {
            if (this != &pr)
            {
                first = std::forward<T1>(pr.first);
                second = std::forward<T2>(pr.second);
                return *this;
            }
        }

    };

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& x, const pair<T1,T2>& y)
	{
		return (x.first == y.first && x.second == y.second);
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& x, const pair<T1,T2>& y)
	{
		return (!(x==y));
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& x, const pair<T1,T2>& y)
	{
		return (y < x);
	}
    
	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& x, const pair<T1,T2>& y)
	{
		return (x.first < y.first || (!(y.first < x.first) && x.second < y.second));
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& x, const pair<T1,T2>& y)
	{
		return (!(y < x));
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& x, const pair<T1,T2>& y)
	{
		return (!(x < y));
	}

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x, y) );
	};

}
#endif