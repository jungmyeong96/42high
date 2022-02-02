#ifndef SPACIALIZED_TP_HPP
# define SPACIALIZED_TP_HPP

namespace ft
{

	enum Color
	{
		RED,
		BLACK,
		DBLACK
	};

    template<bool B, class T = void>
    struct enable_if {};
    
    template<class T>
    struct enable_if<true, T> 
    {
        typedef T type;
    };


    template <typename T>
    struct is_integral //T value삭제
    {
        static const bool value = false;
    };

    template <>
    struct is_integral<bool> {static const bool value = true;};

    template <>
    struct is_integral<char> {static const bool value = true;};

    template <>
    struct is_integral<signed char> {static const bool value = true;};

    template <>
    struct is_integral<short int> {static const bool value = true;};

    template <>
    struct is_integral<int> {static const bool value = true;};

    template <>
    struct is_integral<long int> {static const bool value = true;};

    template <>
    struct is_integral<long long int> {static const bool value = true;};

    template <>
    struct is_integral<unsigned char> {static const bool value = true;};

    template <>
    struct is_integral<unsigned short int> {static const bool value = true;};

    template <>
    struct is_integral<unsigned int> {static const bool value = true;};

    template <>
    struct is_integral<unsigned long int> {static const bool value = true;};

    template <>
    struct is_integral<unsigned long long int> {static const bool value = true;};

    template <class InputIterator1, class InputIterator2>
    bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
    {
        while (first1!=last1) 
        {
            if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
            return false;
            ++first1; ++first2;
        }
        return true;
    }

    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template <bool isConst, typename isFalse, typename isTrue>
    struct ChooseConst {};

    template <typename isFalse, typename isTrue>
    struct ChooseConst<false, isFalse, isTrue>
    {
        typedef isFalse type;
    };

    template <typename isFalse, typename isTrue>
    struct ChooseConst<true, isFalse, isTrue>
    {
        typedef isTrue type;
    };

}


#endif