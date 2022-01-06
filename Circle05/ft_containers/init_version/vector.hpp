#ifndef vector_HPP
#define vector_HPP

# include <iostream>
# include <memory>
# include "VectorIterator.hpp"
# include "ReverseIterator.hpp"
//# include "Pair.hpp"
# include "spacialized_tp.hpp"

namespace ft
{
    template< typename T >
    class vector
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
            typedef std::allocator<T>  allocator_type;
            // typedef ptrdiff_t difference_type;

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
            iterator begin() { return (iterator(this->ft_start));};   ///< 시작부분 포인터
            const_iterator begin() const { return const_iterator(this->ft_start);};
            iterator end() { return (iterator(this->ft_start + this->ft_size)); };
            const_iterator end() const { return const_iterator(this->ft_start + this->ft_size); };

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

    template < typename T >
    vector< T >::vector(): ft_start(nullptr), ft_capacity(0), ft_size(0) 
    {
        this->ft_start = alloc.allocate(0);
    }

    template < typename T >
    vector< T >::vector(size_type n, const_reference val): ft_start(nullptr), ft_capacity(0), ft_size(0)
    {
        this->ft_start = alloc.allocate(n);
        this->ft_size = n;
        std::uninitialized_fill(this->ft_start, this->ft_start + this->ft_size, val);
        this->ft_capacity = n; // +4를 해야하는지?
    }

    template < typename T >
    template <class InputIterator>
    vector< T >::vector(InputIterator start, InputIterator end,
            typename ft::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type*):
        ft_start(nullptr), ft_capacity(0), ft_size(0) //구현 필요
    {
        this->assign(start, end);
    }

    template < typename T >
    vector< T >::vector(const vector & val): //복사생성자
        ft_start(nullptr), ft_capacity(0), ft_size(0)
    {
        if (this != &val)
        {
            this->ft_start = alloc.allocate(val.ft_capacity); //사이즈만큼 할당
            std::uninitialized_copy(val.begin(), val.end(), this->ft_start);
            this->ft_size = val.ft_size;
            this->ft_capacity = val.ft_capacity;
        }
    }

    template < typename T >
    vector< T >::~vector()
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
    vector< T >& vector< T >::operator= ( const vector< T > &rhs )
    {
        vector< T > temp(rhs);
        swap(temp);
        return (*this);
    }

    template < typename T >
    void vector<T>::resize(size_type size, value_type val)
    {
        while (this->ft_size > size)
            pop_back();
        while (this->ft_size < size)
            push_back(val);

    }

    template < typename T >
    void vector<T>::reserve(size_type size)
    {
        if (this->ft_capacity < size)
        {
            size_type idx = this->ft_size;
            pointer tmp = alloc.allocate(size); //size가 과도하게들어오면?
            for (size_type i = 0; i < this->ft_size; i++)
				tmp[i] = this->ft_start[i];
            while (this->ft_start + idx != this->ft_start)
            {
                idx--;
                alloc.destroy(this->ft_start + idx);
            }
            //alloc.deallocate(this->ft_start, this->ft_capacity);
            this->ft_start = tmp;
            this->ft_capacity = size;
        }
    }

    template < typename T >
    typename vector<T>::reference vector<T>::at(size_type idx)
    {
        if (idx >= this->ft_size)
            throw std::out_of_range("vector::out_of_range\n");
        return (this->ft_start[idx]);
    }

    template < typename T >
    typename vector<T>::const_reference vector<T>::at(size_type idx) const
    {
        if (idx >= this->ft_size)
            throw std::out_of_range("vector::out_of_range\n");
        return (this->ft_start[idx]);
    }

    template < typename T >
    typename vector<T>::reference vector<T>::front(void) 
    {
		return (this->ft_start[0]);
	}

    template < typename T >
	typename vector<T>::const_reference vector<T>::front(void) const 
    {
		return (this->ft_start[0]);
	}

    template < typename T >
	typename vector<T>::reference vector<T>::back(void) 
    {
		return (this->ft_start[this->ft_size - 1]);
	}

    template < typename T >
	typename vector<T>::const_reference vector<T>::back(void) const 
    {
		return (this->ft_start[this->ft_size - 1]);
	}

    template < typename T >
    void vector<T>::assign(size_type size, const_reference val)
    {
        this->clear();
        this->insert(this->begin(), size, val);
    }

    template < typename T >
    template < class InputIterator >
    void vector<T>::assign(InputIterator start, InputIterator end,
            		typename ft::enable_if<!std::is_integral<InputIterator>::value,
                    InputIterator>::type*)
    {
        this->clear();
        this->insert(this->begin(), start, end);
    }

    template < typename T >
	void vector<T>::push_back(const_reference val)
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
	void vector<T>::pop_back(void)
    {
        if (this->ft_size)
            this->ft_size--;
    }

    template < typename T >
    typename vector<T>::iterator vector<T>::insert (iterator pos, const_reference val)
    {
        size_type idx;
        
        idx = 0;
        while (this->begin() + idx != pos) //오버플로우로 터지면 어떡하지
            ++idx;
        insert(pos, 1, val);
        return (this->begin() + idx); //새롭게 삽입된 요소 중 첫번째 요소 이터레이터
    }

    template < typename T >
    void vector<T>::insert (iterator pos, size_type n, const_reference val)
    {
        size_type idx;
        
        idx = 0;
        while (this->begin() + idx != pos) //오버플로우로 터지면 어떡하지
            ++idx;
        this->reserve(this->ft_size + n);
        for (size_type tmp = this->ft_size; tmp > idx ; tmp--)
            ft_start[tmp] = ft_start[tmp - n];
        std::uninitialized_fill(this->ft_start + idx, this->ft_start + idx + n, val);
        this->ft_size += n;
    }

    template < typename T >
    template <class InputIterator>
    void vector<T>::insert (iterator pos, InputIterator start, InputIterator end,
            		typename ft::enable_if<!std::is_integral<InputIterator>::value,
                    InputIterator>::type*)
    {
        while (start != end)
            pos = this->insert(pos, *start++) + 1;
    }

    template < typename T >
    typename vector<T>::iterator vector<T>::erase (iterator pos)
    {
        iterator tmp;
        size_type idx;

        tmp = pos;
        idx = 0;
        while (this->begin() != tmp - idx)
            ++idx;
        alloc.destroy(this->ft_start + idx);
        std::uninitialized_copy(tmp, this->end(), this->ft_start + idx);
        --this->ft_size;
        return (pos);
    }

    template < typename T >
    typename vector<T>::iterator vector<T>::erase (iterator start, iterator end)
    {
        while (start != end)
            this->erase(end--);
        return(start);
    }

    template < typename T >
    void vector< T >::swap ( vector< T > &rhs )
    {
        std::swap( ft_start, rhs.ft_start );
        std::swap( ft_size, rhs.ft_size );
        std::swap( ft_capacity, rhs.ft_capacity );
    }

    template < typename T >
    void vector< T >::clear() //재할당이 보장 되지 않으며 이 함수를 호출 하여 벡터 용량 이 변경된다는 보장도 없습니다. 재할당을 강제하는 일반적인 대안은 swap 을 사용하는 것입니다 . ?? swap은 재할당보장?
    {
        erase(this->begin(), this->end());
    }

    /// Non Member Funtion
    template<typename T>
    bool operator==(vector<T> const &lhs, vector<T> const &rhs) {
        if (lhs.size() != rhs.size())
            return (false);
        return(ft::equal(lhs.begin(), lhs.end(), rhs.begin())); //재구현해야함
    }

    template<typename T>
    bool operator!=(vector<T> const &lhs, vector<T> const &rhs) {
        return (!(lhs == rhs));
    }

    template<typename T>
    bool operator<(vector<T> const &lhs, vector<T> const &rhs) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); //재구현해야함
    }

    template<typename T>
    bool operator<=(vector<T> const &lhs, vector<T> const &rhs) {
        return (!(rhs < lhs));
    }

    template<typename T>
    bool operator>(vector<T> const &lhs, vector<T> const &rhs) {
        return (rhs < lhs);
    }

    template<typename T>
    bool operator>=(vector<T> const &lhs, vector<T> const &rhs) {
        return (!(lhs < rhs));
    }

    template<typename T>
    void swap(vector<T> &x, vector<T> &y) {
        x.swap(y);
    }

}

#endif