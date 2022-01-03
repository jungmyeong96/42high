#ifndef VECTOR_HPP
#define VECTOR_HPP

# include <iostream>
# include <memory>
# include "VectorIterator.hpp"
# include "ReverseIterator.hpp"
//# include "Pair.hpp"
# include "spacialized_tp.hpp"

namespace ft
{
    template< typename T > //allocator의 초기화?
    class Vector
    {
        public:
            typedef T value_type; //타입지정
            typedef T& reference;
            typedef const T& const_reference;
            typedef T* pointer;
            typedef const T* const_pointer;
            typedef size_t size_type;
            typedef VectorIterator<T> iterator;
            typedef VectorIterator<T const> const_iterator;
            typedef ReverseIterator<T> reverse_iterator;
            typedef ReverseIterator<T const> const_reverse_iterator;
            //typedef Alloc allocator_type;
            // typedef ptrdiff_t difference_type;

            private:
                pointer ft_start;
                size_type ft_capacity;
                size_type ft_size;
                std::allocator<T> alloc;
        

        public:
            //Canonical
            explicit Vector();
            explicit Vector(size_type n, const_reference val = value_type());
            template <class InputIterator>
            Vector(InputIterator start, InputIterator end,
            		typename std::enable_if<!std::is_integral<InputIterator>::value,
                    InputIterator>::type* = nullptr); //구현해야함
            Vector(const Vector & val);
            virtual ~Vector();
            Vector& operator= ( const Vector& );


            //Normal Iterators
            iterator begin() { return (iterator(this->ft_start));};   ///< 시작부분 포인터
            const_iterator begin() const { return const_iterator(this->ft_start);};
            iterator end() { return (iterator(this->ft_start + this->ft_size)); };
            const_iterator end() const { return iterator(this->ft_start + this->ft_size); };


            //Reverse Iterators
            reverse_iterator rbegin() { return (reverse_iterator(this->ft_start + this->ft_size - 1));}   ///< 끝에서 하나뺀 위치 포인터 (alloc시 4바이크만큼 더 할당됨)
            const_reverse_iterator rbegin() const { return const_reverse_iterator(this->ft_start + this->ft_size - 1);};
            reverse_iterator rend() { return (reverse_iterator(this->ft_start - 1)); }; //끝은 항상 마지막 다음 포인터를 가리킴
            const_reverse_iterator rend() const { return const_reverse_iterator(this->ft_start - 1); };


            //Capacity
            size_type size() const { return (this->ft_size); };
            size_type max_size() const { return (this->alloc.max_size()); };
            void resize(size_type size, value_type val = value_type());
            void reserve(size_type size);
            size_type capacity(void) const { return (this->ft_capacity); };
            bool empty() const {return (this->ft_size = 0); };


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
            void assign(size_type, const_reference);
            template <class InputIterator>
            void assign(InputIterator, InputIterator);
            void push_back(const_reference);
            void pop_back(void);
            iterator insert (iterator, const_reference);	
            void insert (iterator, size_type, const_reference);	
            template <class InputIterator>
            void insert (iterator, InputIterator, InputIterator);
            iterator erase (iterator position);
            iterator erase (iterator first, iterator last);
            void swap (Vector & );
            void clear ();

            //Allocator
            std::allocator<T> get_allocator() const { return (std::allocator<T>());} //?

    };

    template < typename T >
    Vector< T >::Vector(): ft_start(nullptr), ft_capacity(0), ft_size(0) 
    {
        this->ft_start = alloc.allocate(0);
    };

    template < typename T >
    Vector< T >::Vector(size_type n, const_reference val): ft_start(nullptr), ft_capacity(0), ft_size(0)
    {
        this->ft_start = alloc.allocate(n);
        this->ft_size = n;
        std::uninitialized_fill(this->ft_start, this->ft_start + this->ft_size, val);
        this->ft_capacity = n; // +4를 해야하는지?
    }

    template < typename T >
    template <class InputIterator>
    Vector< T >::Vector(InputIterator start, InputIterator end,
            typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type*):
        ft_start(nullptr), ft_capacity(0), ft_size(0) //구현 필요
    {
        int len;
        InputIterator tmp;

        len = 0;
        tmp = start;
        while (start != end)
        {
            ++start;
            ++len;
        }
        this->ft_start = alloc.allocate(len); //사이즈만큼 할당
        //std::uninitialized_copy(tmp, end, this->ft_start);
        for (size_type i = 0; i < len; i++)
            this->ft_start[i] = tmp++;
        this->ft_size = len;
        this->ft_capacity = len; // +4를 해야하는지?
    }

    template < typename T >
    Vector< T >::Vector(const Vector & val): //복사생성자
        ft_start(nullptr), ft_capacity(0), ft_size(0)
    {
        if (this != &val)
        {
            this->ft_start = alloc.allocate(val.ft_end - val.ft_start); //사이즈만큼 할당
            std::uninitialized_copy(val.ft_start, val.ft_end, this->ft_start);
            this->ft_size = val.ft_size;
            this->ft_capacity = val.ft_capacity;
        }
    }

    template < typename T >
    Vector< T >::~Vector()
    {
        if (this->ft_start)
        {
            pointer it; //iterator쓰면 destroy에서 오류
            it = (this->ft_start + this->ft_size); //임시 iterator로 바꿔야함
            while (it != this->ft_start)
                alloc.destroy(--it);
            alloc.deallocate(ft_start, ft_capacity);
        }
        this->ft_start = nullptr;
    }

    template < typename T >
    Vector< T >& Vector< T >::operator= ( const Vector< T > &rhs )
    {
        Vector< T > temp(rhs);
        swap(temp);
        return (*this);
    }

    template < typename T >
    void Vector<T>::resize(size_type size, value_type val)
    {
        this->reserve(size);
        if (this->ft_size < size)
            std::uninitialized_fill(this->ft_start + this->ft_size, this->ft_start + size, val);
        if (this->ft_size > size)
            this->ft_size = size;
    }

    template < typename T >
    void Vector<T>::reserve(size_type size)
    {
        if (this->ft_capacity < size)
        {
            size_type idx = this->ft_size;
            pointer tmp = alloc.allocate(size); //size가 과도하게들어오면?
            for (size_type i = 0; i < this->ft_capacity; i++)
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


    template < typename T >
    typename Vector<T>::reference Vector<T>::at(size_type idx)
    {
        if (idx >= this->ft_size)
            throw std::out_of_range("vVector::out_of_range\n");
        return (this->ft_start[idx]);
    }

    template < typename T >
    typename Vector<T>::const_reference Vector<T>::at(size_type idx) const
    {
        if (idx >= this->ft_size)
            throw std::out_of_range("Vector::out_of_range\n");
        return (this->ft_start[idx]);
    }

    template < typename T >
    typename Vector<T>::reference Vector<T>::front(void) 
    {
		return (this->ft_start[0]);
	}

    template < typename T >
	typename Vector<T>::const_reference Vector<T>::front(void) const 
    {
		return (this->ft_start[0]);
	}

    template < typename T >
	typename Vector<T>::reference Vector<T>::back(void) 
    {
		return (this->ft_start[this->ft_size - 1]);
	}

    template < typename T >
	typename Vector<T>::const_reference Vector<T>::back(void) const 
    {
		return (this->ft_start[this->ft_size - 1]);
	}

    template < typename T >
    void Vector<T>::assign(size_type size, const_reference val)
    {
        this->reserve(size); //용량체크 clear?
        std::uninitialized_fill(this->ft_start, this->ft_start + size, val); //size만큼 할당
        while(this->ft_size-- > size)
            alloc.destroy(this->ft_start + this->ft_size);
    }

    template < typename T >
    template < class InputIterator >
    void Vector<T>::assign(InputIterator start, InputIterator end)
    {
        int len;
        InputIterator tmp;

        len = 0;
        tmp = start;
        while (start != end)
        {
            ++start;
            ++len;
        }
        this->reserve(len); //용량체크
        //std::uninitialized_copy(tmp, end, this->ft_start); //size만큼 할당
        for (size_type i = 0; i < len; i++)
            this->ft_start[i] = tmp++;
        while(this->ft_size-- > len)
           alloc.destroy(this->ft_start + this->ft_size);
    }

    template < typename T >
	void Vector<T>::push_back(const_reference val)
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

    template < typename T >
	void Vector<T>::pop_back(void)
    {
        if (this->ft_size)
            this->ft_size--;
    }

    template < typename T >
    typename Vector<T>::iterator Vector<T>::insert (iterator pos, const_reference val)
    {
        size_type idx;
        iterator it;
        
        it = this->begin();
        idx = 0;
        while (it + idx != pos) //오버플로우로 터지면 어떡하지
            ++idx;
        this->insert(pos, 1, val);
        return (this->begin() + idx); //새롭게 삽입된 요소 중 첫번째 요소 이터레이터
    }

    template < typename T >
    void Vector<T>::insert (iterator pos, size_type n, const_reference val)
    {
        size_type idx;
        iterator it;
        
        it = this->begin();
        idx = 0;
        while (it + idx != pos) //오버플로우로 터지면 어떡하지
            ++idx;
        this->reserve(this->size + n);
        uninitialized_copy(this->ft_start + idx + 1, this->ft_start + ft_size, this->ft_start + idx + n);
        uninitialized_fill(this->ft_start + idx, this->ft_start + idx + n, val);
        this->ft_size += n;
    }

    template < typename T >
    template <class InputIterator>
    void Vector<T>::insert (iterator pos, InputIterator start, InputIterator end)
    {
        size_type idx;
        iterator it;
        InputIterator tmp;
        int len;

        tmp = start;
        it = this->begin();
        idx = 0;
        while (it + idx != pos && idx < this->ft_size) //오버플로우로 터지면 어떡하지
            ++idx;
        len = 0;
        while (start != end)
        {
            ++start;
            ++len;
        }
        this->reserve(this->ft_size + len);
        std::uninitialized_copy(this->ft_start + idx, this->ft_start + ft_size, this->ft_start + len + idx);        
        //std::uninitialized_copy(tmp, end, this->ft_start + idx);
        for (size_type i = 0; i < len; i++)
            this->ft_start[i] = tmp++;
        this->ft_size += len;
    }

    template < typename T >
    typename Vector<T>::iterator Vector<T>::erase (iterator pos)
    {
        //pos위치, 끝값 destroy?
        std::uninitialized_copy(this->ft_start + pos + 1, this->ft_size, this->ft_start + pos);
        --this->ft_size;
    }

    template < typename T >
    typename Vector<T>::iterator Vector<T>::erase (iterator start, iterator end)
    {
        //pos위치, 끝값 destroy?
        std::uninitialized_copy(this->ft_start + end, this->ft_size, start);
        this->ft_size -= (end - start);
    }

    template < typename T >
    void Vector< T >::swap ( Vector< T > &rhs )
    {
        std::swap( ft_start, rhs.ft_start );
        std::swap( ft_size, rhs.ft_size );
        std::swap( ft_capacity, rhs.ft_capacity );
    }

    template < typename T >
    void Vector< T >::clear() //재할당이 보장 되지 않으며 이 함수를 호출 하여 벡터 용량 이 변경된다는 보장도 없습니다. 재할당을 강제하는 일반적인 대안은 swap 을 사용하는 것입니다 . ?? swap은 재할당보장?
    {
        while (this->ft_start + this->size != this->ft_start)
        {
            --this->size;
            alloc.destroy(this->ft_start + this->size);
        }
        this->ft_size = 0; //이제필요없음
    }

    /// Non Member Funtion
    template<typename T>
    bool operator==(Vector<T> const &lhs, Vector<T> const &rhs) {
        if (lhs.size() != rhs.size())
            return (false);
        return(ft::equal(lhs.begin(), lhs.end(), rhs.begin())); //재구현해야함
    }

    template<typename T>
    bool operator!=(Vector<T> const &lhs, Vector<T> const &rhs) {
        return (!(lhs == rhs));
    }

    template<typename T>
    bool operator<(Vector<T> const &lhs, Vector<T> const &rhs) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); //재구현해야함
    }

    template<typename T>
    bool operator<=(Vector<T> const &lhs, Vector<T> const &rhs) {
        return (!(rhs < lhs));
    }

    template<typename T>
    bool operator>(Vector<T> const &lhs, Vector<T> const &rhs) {
        return (rhs < lhs);
    }

    template<typename T>
    bool operator>=(Vector<T> const &lhs, Vector<T> const &rhs) {
        return (!(lhs < rhs));
    }

    template<typename T>
    void swap(Vector<T> &x, Vector<T> &y) {
        x.swap(y);
    }

}

#endif