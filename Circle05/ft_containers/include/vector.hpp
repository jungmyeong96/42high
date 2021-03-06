#ifndef VECTOR_HPP
#define VECTOR_HPP

# include <iostream>
#include <cstddef>
# include <memory>
# include "VectorIterator.hpp"
# include "ReverseIterator.hpp"
# include "SpacializedTp.hpp"

namespace ft
{
    template< typename T, typename Alloc = std::allocator<T> >
    class vector
    {
        public:
            typedef T value_type;
            typedef T& reference;
            typedef const T& const_reference;
            typedef T* pointer;
            typedef const T* const_pointer;
            typedef size_t size_type;
            typedef typename ft::VectorIterator<T, false>      iterator;
            typedef typename ft::VectorIterator<T, true>       const_iterator;
            typedef typename ft::reverse_iterator<T, false>  reverse_iterator;
            typedef typename ft::reverse_iterator<T, true>   const_reverse_iterator;
            typedef Alloc  allocator_type;

        private:
            pointer ft_start;
            size_type ft_capacity;
            size_type ft_size;
            std::allocator<T> alloc;
        
        public:
            //Canonical
            explicit vector();
            explicit vector(size_type n, const_reference val = value_type());
            template <class InputIterator>
            vector(InputIterator start, InputIterator end,
            		typename ft::enable_if<!std::is_integral<InputIterator>::value,
                    InputIterator>::type* = nullptr);
            vector(const vector & val);
            virtual ~vector();
            vector& operator= ( const vector& );

            //Normal Iterators
            iterator begin() { return (iterator(this->ft_start));};
            const_iterator begin() const { return const_iterator(this->ft_start);};
            iterator end() { return (iterator(this->ft_start + this->ft_size)); };
            const_iterator end() const { return const_iterator(this->ft_start + this->ft_size); };

            //Reverse Iterators
            reverse_iterator rbegin() { return (reverse_iterator(this->ft_start + this->ft_size));}   ///< ????????? ????????? ?????? ????????? (alloc??? 4??????????????? ??? ?????????)
            const_reverse_iterator rbegin() const { return const_reverse_iterator(this->ft_start + this->ft_size);};
            reverse_iterator rend() { return (reverse_iterator(this->ft_start)); }; //?????? ?????? ????????? ?????? ???????????? ?????????
            const_reverse_iterator rend() const { return const_reverse_iterator(this->ft_start); };

            //Capacity
            size_type size() const { return (this->ft_size); };
            size_type max_size() const { return (this->alloc.max_size()); };
            void resize(size_type size, value_type val = value_type());
            void reserve(size_type size);
            size_type capacity(void) const { return (this->ft_capacity); };
            bool empty() const { return (this->ft_size == 0); };

            //Element Access
            value_type& operator[] (size_type i) {return this->ft_start[i];};
            const value_type& operator[] (size_type i) const {return this->ft_start[i];};
            reference at(size_type);
            const_reference at(size_type) const ;
            reference front(void) ;
            const_reference front(void) const ;
            reference back(void) ;
            const_reference back(void) const ;

            //Modifiers
            void assign(size_type, const_reference val = value_type());
            template <class InputIterator>
            void assign(InputIterator, InputIterator,
            		typename ft::enable_if<!std::is_integral<InputIterator>::value,
                    InputIterator>::type* = nullptr);
            void push_back(const_reference val = value_type());
            void pop_back(void);
            iterator insert (iterator, const_reference val = value_type());	
            void insert (iterator, size_type, const_reference val = value_type());	
            template <class InputIterator>
            void insert (iterator, InputIterator, InputIterator,
            		typename ft::enable_if<!std::is_integral<InputIterator>::value,
                    InputIterator>::type* = nullptr);
            iterator erase (iterator position);
            iterator erase (iterator first, iterator last);
            void swap (vector & );
            void clear ();

            //Allocator
            allocator_type get_allocator() const { return (allocator_type());} //?
    
    };

    template < typename T , typename Alloc >
    vector< T, Alloc >::vector(): ft_start(nullptr), ft_capacity(0), ft_size(0) 
    {
        this->ft_start = alloc.allocate(0);
    }

    template < typename T , typename Alloc >
    vector< T, Alloc >::vector(size_type n, const_reference val): ft_start(nullptr), ft_capacity(0), ft_size(0)
    {
        this->ft_start = alloc.allocate(n);
        this->ft_size = n;
        std::uninitialized_fill(this->ft_start, this->ft_start + this->ft_size, val);
        this->ft_capacity = n;
    }

    template < typename T , typename Alloc >
    template <class InputIterator>
    vector< T, Alloc >::vector(InputIterator start, InputIterator end,
            typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type*):
        ft_start(nullptr), ft_capacity(0), ft_size(0) //?????? ??????
    {
        this->assign(start, end);
    }

    template < typename T , typename Alloc >
    vector< T, Alloc >::vector(const vector & val): //???????????????
        ft_start(nullptr), ft_capacity(0), ft_size(0)
    {
        if (this != &val)
        {
            this->ft_start = alloc.allocate(val.ft_capacity); //??????????????? ??????
            std::uninitialized_copy(val.begin(), val.end(), this->ft_start);
            this->ft_size = val.ft_size;
            this->ft_capacity = val.ft_capacity;
        }
    }

    template < typename T , typename Alloc >
    vector< T, Alloc >::~vector()
    {
        if (this->ft_start)
        {
            pointer it; //iterator?????? destroy?????? ??????
            it = (this->ft_start + this->ft_size); //?????? iterator??? ????????????
            while (it != this->ft_start)
                alloc.destroy(--it);
            alloc.deallocate(ft_start, ft_capacity);
        }
        this->ft_start = nullptr;
    }

    template < typename T , typename Alloc >
    vector< T, Alloc >& vector< T, Alloc >::operator= ( const vector< T, Alloc > &rhs )
    {
        vector< T, Alloc > temp(rhs);
        swap(temp);
        return (*this);
    }

    template < typename T , typename Alloc >
    void vector< T, Alloc >::resize(size_type size, value_type val)
    {
        while (this->ft_size > size)
            pop_back();
        while (this->ft_size < size)
            push_back(val);

    }

    template < typename T , typename Alloc >
    void vector< T, Alloc >::reserve(size_type size)
    {
        if (this->ft_capacity < size)
        {
            size_type idx = this->ft_size;
            pointer tmp = alloc.allocate(size);
            for (size_type i = 0; i < this->ft_size; i++)
				tmp[i] = this->ft_start[i];
            while (this->ft_start + idx != this->ft_start)
            {
                idx--;
                alloc.destroy(this->ft_start + idx);
            }
            alloc.deallocate(this->ft_start, this->ft_capacity);
            this->ft_start = tmp;
            this->ft_capacity = size;
        }
    }

    template < typename T , typename Alloc >
    typename vector< T, Alloc >::reference vector< T, Alloc >::at(size_type idx)
    {
        if (idx >= this->ft_size)
            throw std::out_of_range("vector::out_of_range\n");
        return (this->ft_start[idx]);
    }

    template < typename T , typename Alloc >
    typename vector< T, Alloc >::const_reference vector< T, Alloc >::at(size_type idx) const
    {
        if (idx >= this->ft_size)
            throw std::out_of_range("vector::out_of_range\n");
        return (this->ft_start[idx]);
    }

    template < typename T , typename Alloc >
    typename vector< T, Alloc >::reference vector< T, Alloc >::front(void) 
    {
		return (this->ft_start[0]);
	}

    template < typename T , typename Alloc >
	typename vector< T, Alloc >::const_reference vector< T, Alloc >::front(void) const 
    {
		return (this->ft_start[0]);
	}

    template < typename T , typename Alloc >
	typename vector< T, Alloc >::reference vector< T, Alloc >::back(void) 
    {
		return (this->ft_start[this->ft_size - 1]);
	}

    template < typename T , typename Alloc >
	typename vector< T, Alloc >::const_reference vector< T, Alloc >::back(void) const 
    {
		return (this->ft_start[this->ft_size - 1]);
	}

    template < typename T , typename Alloc >
    void vector< T, Alloc >::assign(size_type size, const_reference val)
    {
        this->clear();
        this->insert(this->begin(), size, val);
    }

    template < typename T , typename Alloc >
    template < class InputIterator >
    void vector< T, Alloc >::assign(InputIterator start, InputIterator end,
            		typename ft::enable_if<!std::is_integral<InputIterator>::value,
                    InputIterator>::type*)
    {
        this->clear();
        this->insert(this->begin(), start, end);
    }

    template < typename T , typename Alloc >
	void vector< T, Alloc >::push_back(const_reference val)
    {
		if (this->ft_size == this->ft_capacity)
        {
            if (this->ft_capacity >= max_size() / 2)
                this->reserve(max_size());
            if (this->ft_capacity == 0)
                this->reserve(1);
            else
			    this->reserve(this->ft_capacity * 2);
        }
		ft_start[ft_size++] = val;
	}

    template < typename T , typename Alloc >
	void vector< T, Alloc >::pop_back(void)
    {
        if (this->ft_size)
            this->ft_size--;
    }

    template < typename T , typename Alloc >
    typename vector< T, Alloc >::iterator vector< T, Alloc >::insert (iterator pos, const_reference val)
    {
        size_type idx;
        
        idx = 0;
        while (this->begin() + idx != pos)
            ++idx;
        insert(pos, 1, val);
        return (this->begin() + idx);
    }

    template < typename T , typename Alloc >
    void vector< T, Alloc >::insert (iterator pos, size_type n, const_reference val)
    {
        size_type idx;
        size_type old_idx;
        iterator old_end;
        iterator end;
        
        idx = pos - this->begin();
        old_idx = this->end() - this->begin();
        this->resize(this->ft_size + n);
        old_end = this->begin() + old_idx;
        end = this->end(); 
        pos = this->begin() + idx;
        while(old_end != pos)
            *--end = *--old_end;
    	while (n-- > 0)
		    *pos++ = val;
    }

    template < typename T , typename Alloc >
    template <class InputIterator>
    void vector< T, Alloc >::insert (iterator pos, InputIterator start, InputIterator end,
            		typename ft::enable_if<!std::is_integral<InputIterator>::value,
                    InputIterator>::type*)
    {
        while (start != end)
            pos = this->insert(pos, *start++) + 1;
    }

    template < typename T , typename Alloc >
    typename vector< T, Alloc >::iterator vector< T, Alloc >::erase (iterator pos)
    {
        	return (this->erase(pos, pos + 1));
    }

    template < typename T , typename Alloc >
    typename vector< T, Alloc >::iterator vector< T, Alloc >::erase (iterator start, iterator end)
    {
        iterator tmp = start;
	    size_type deleted = end - start;

        while (end != this->end())
        {
            *start = *end;
            ++start;
            ++end;
        }
        while (deleted-- > 0)
            this->alloc.destroy(&this->ft_start[--this->ft_size]);
	    return (tmp);
    }

    template < typename T , typename Alloc >
    void vector< T, Alloc >::swap ( vector< T, Alloc > &rhs )
    {
        std::swap( ft_start, rhs.ft_start );
        std::swap( ft_size, rhs.ft_size );
        std::swap( ft_capacity, rhs.ft_capacity );
    }

    template < typename T , typename Alloc >
    void vector< T, Alloc >::clear()
    {
        erase(this->begin(), this->end());
    }

    /// Non Member Funtion
    template < typename T , typename Alloc >
    bool operator==(vector< T, Alloc > const &lhs, vector< T, Alloc > const &rhs) {
        if (lhs.size() != rhs.size())
            return (false);
        return(ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template < typename T , typename Alloc >
    bool operator!=(vector< T, Alloc > const &lhs, vector< T, Alloc > const &rhs) {
        return (!(lhs == rhs));
    }

    template < typename T , typename Alloc >
    bool operator<(vector< T, Alloc > const &lhs, vector< T, Alloc > const &rhs) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); //??????????????????
    }

    template < typename T , typename Alloc >
    bool operator<=(vector< T, Alloc > const &lhs, vector< T, Alloc > const &rhs) {
        return (!(rhs < lhs));
    }

    template < typename T , typename Alloc >
    bool operator>(vector< T, Alloc > const &lhs, vector< T, Alloc > const &rhs) {
        return (rhs < lhs);
    }

    template < typename T , typename Alloc >
    bool operator>=(vector< T, Alloc > const &lhs, vector< T, Alloc > const &rhs) {
        return (!(lhs < rhs));
    }

    template < typename T , typename Alloc >
    void swap(vector< T, Alloc > &x, vector< T, Alloc > &y) {
        x.swap(y);
    }

}

#endif