#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

//#include "ft.hpp"

// template <class T>
// class Vectoriter
// {
//     public::
//         typedef T value_type;
//         typedef value_type* pointer;
//         typedef value_type const * const_pointer;
//         typedef value_type& reference;
//         typedef value_type const & const_reference;
//         typedef std::ptrdiff_t difference_type;
// };



template< class T>
class Vector
{
    public:
	    typedef T value_type; //타입지정
        //typedef Alloc allocator_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T* pointer;
        typedef const T* const_pointer;
        //typedef Vectoriter<value_type> iterator;
        //typedef Vectoriter<value_type const> const_iterator;
        typedef T* iterator;
        typedef const T* const_iterator;
        // typedef Vectoriter<iterator> reverse_iterator;
        // typedef Vectoriter<const_iterator> const_reverse_iterator;
        // typedef ptrdiff_t difference_type;
         typedef size_t size_type;
    private:
        pointer ft_start;
        pointer ft_end;
        size_type ft_capacity;
        size_type ft_size;
        std::allocator<T> alloc;
        void create(size_type, const_reference);
        void create(const_iterator, const_iterator);
		void destroy ();
		void Swap (Vector & );
    public:
        Vector():
            ft_start(nullptr), ft_end(nullptr), ft_capacity(0), ft_size(0) {};
        explicit Vector(size_type n, const_reference val = value_type()): 
    		ft_start(nullptr), ft_end(nullptr), ft_capacity(0), ft_size(0) //왜 explicit쓰고 assign하는지 잘모르겠음  
        {
        	this->create(n, val);
        }
        Vector(const_iterator start, const_iterator end)://일단 복사생성자와 똑같이 작동함
            ft_start(nullptr), ft_end(nullptr), ft_capacity(0), ft_size(0)
        {
            this->create(start, end);
        }
		Vector(const Vector & val): //복사생성자
			ft_start(nullptr), ft_end(nullptr), ft_capacity(0), ft_size(0)
		{
			this->create(val.ft_start, val.ft_end);
		}
		virtual ~Vector()
		{
			destroy();
		}
		Vector& operator= ( const Vector& ); 
		iterator begin() { return this->ft_start;}   ///< data iterator
		const_iterator begin() const { return this->ft_start;};
		iterator end() { return this->ft_end;};
		const_iterator end() const { return this->ft_end;};
};

template < typename T >
Vector< T >& Vector< T >::operator= ( const Vector< T > &rhs )
{
    Vector< T > temp(rhs);
    Swap(temp);
    return (*this);
}

template < typename T >
void Vector< T >::Swap ( Vector< T > &rhs )
{
    std::swap( ft_start, rhs.ft_start );
    std::swap( ft_end , rhs.ft_end  );
    std::swap( ft_size, rhs.ft_size );
	std::swap( ft_capacity, rhs.ft_capacity );
}

template < typename T >
void Vector< T >::create(size_type n, const_reference val)
{
    ft_start = alloc.allocate(n);
    ft_end = ft_start + n;
	ft_capacity = n; // +4를 해야하는지?
	ft_size = n;
    std::uninitialized_fill(ft_start, ft_end, val);
}

template < typename T >
void Vector< T >::create(const_iterator start, const_iterator end)
{
    ft_start = alloc.allocate(end - start); //사이즈만큼 할당
    ft_end = std::uninitialized_copy(start, end, ft_start);
	ft_capacity = end - start; // +4를 해야하는지?
	ft_size = end - start;
}

template < typename T >
void Vector< T >::destroy()
{
	if (ft_start)
	{
		T * it = ft_end; //임시 iterator로 바꿔야함
		while (it != ft_start)
			alloc.destroy(--it);
		alloc.deallocate(ft_start, ft_end - ft_start);
	}
	ft_start = nullptr;
	ft_end = nullptr;
}

// template < typename T >
// Vector< T >::iterator            Vector< T >::begin       ()          { return this->ft_start;          }   ///< data iterator
// template < typename T >
// Vector< T >::const_iterator      Vector< T >::begin       ()  const   { return this->ft_start;          }   ///< data const_iterator
// template < typename T >
// Vector< T >::iterator            Vector< T >::end         ()          { return this->ft_end;         }   ///< avail iterator
// template < typename T >
// Vector< T >::const_iterator      Vector< T >::end         ()  const   { return this->ft_end;         }   ///< avail const_iterator

// template < typename T > //밑으로 내리면 못찾음 왜?
// Vector< T >::Vector():
//     ft_start(nullptr), ft_end(nullptr), ft_capacity(0), ft_size(0)
// {
//     ;
// }

// template < typename T >
// Vector< T >::Vector(size_type n, const_reference val):
//     ft_start(nullptr), ft_end(nullptr), ft_capacity(0), ft_size(0)
// {
//     this->create(n, val);
// }

// template < typename T >
// Vector< T >::Vector(const_iterator start, const_iterator end):
//     ft_start(nullptr), ft_end(nullptr), ft_capacity(0), ft_size(0)
// {
//     this->create(start, end);
// }


#endif