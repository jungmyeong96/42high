#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "SpacializedTp.hpp"

namespace ft
{

    template < typename T , bool B>
    struct iterator_traits
    {
        typedef T value_type; //타입지정
        typedef typename ChooseConst<B, T&, const T&>::type     reference;
        typedef typename ChooseConst<B, T*, const T*>::type     pointer;
        typedef std::ptrdiff_t difference_type;
    };

    template <class T, bool B>
    class VectorIterator
    {
        public:
            typedef iterator_traits<T, B>               iterator_traits;
            typedef typename iterator_traits::value_type         value_type;
            typedef typename iterator_traits::reference          reference;
            typedef typename iterator_traits::pointer            pointer;
            typedef typename iterator_traits::difference_type    difference_type;
        private :
            pointer ptr;
            
        public:
            VectorIterator() : ptr(0) {};
            VectorIterator(pointer offset) : ptr(offset) {};
            VectorIterator(VectorIterator<T, false> const &tmp): ptr(tmp.getptr()) {};
            virtual ~VectorIterator() {};

            //Operator assign
            VectorIterator &operator=(VectorIterator const &tmp)
            {
                if (this != &tmp)
                    this->ptr = tmp.getptr();
                return (*this);
            }

            //Operator Access

            reference operator*() const { return (*this->ptr); };
            pointer operator->() const { return (this->ptr); };
            reference operator[](int idx) const { return (*(this->ptr + idx)); };
            
            //Plus Operation
            VectorIterator operator+(int val) const
            {
                VectorIterator tmp(*this);
                return (tmp += val);
            }
            friend VectorIterator operator+(difference_type n, const VectorIterator<T, B>& x)
            {
                return VectorIterator<T, B>(x + n);
            }
            VectorIterator &operator+=(int val)
            {
                this->ptr += val;
                return (*this);
            }
            VectorIterator operator++(int)
            {
                VectorIterator tmp(*this);
                this->ptr = this->ptr + 1;
                return (tmp);
            }
            VectorIterator &operator++()
            {
                this->ptr = this->ptr + 1;
                return (*this);
            }

            //Minus Operation
            VectorIterator operator-(int val) const
            {
                VectorIterator tmp(*this);
                return (tmp -= val);
            }
            difference_type operator-(VectorIterator const &other) const
            {
                return (this->ptr - other.getptr());
            }
            VectorIterator &operator-=(int val)
            {
                this->ptr = this->ptr - val;
                return (*this);
            }
            VectorIterator operator--(int)
            {
                VectorIterator tmp(*this);
                this->ptr = this->ptr - 1;
                return(tmp);
            }
            VectorIterator &operator--()
            {
                this->ptr = this->ptr - 1;
                return (*this);
        	}


            //Operator compare
            bool operator==(const VectorIterator &other) const
            {
                if (this->ptr == other.getptr())
                    return (1);
                return (0);
            }
            bool operator==(const VectorIterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                VectorIterator<T, true> ano = other;  
                if (this->ptr == ano.getptr())
                    return (1);
                return (0);
            }
            bool operator!=(const VectorIterator &other) const
            {
                if (this->ptr != other.getptr())
                    return (1);
                return (0);
            }
            bool operator!=(const VectorIterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                VectorIterator<T, true> ano = other;  
                if (this->ptr != ano.getptr())
                    return (1);
                return (0);
            }
            bool operator>(const VectorIterator &other) const
			{
				if (this->ptr > other.getptr())
					return (1);
				return (0);
			}
            bool operator>(const VectorIterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                VectorIterator<T, true> ano = other;  
                if (this->ptr > ano.getptr())
                    return (1);
                return (0);
            }
			bool operator<(const VectorIterator &other) const
			{
				if (this->ptr < other.getptr())
					return (1);
                return (0);
			}
            bool operator<(const VectorIterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                VectorIterator<T, true> ano = other;  
                if (this->ptr < ano.getptr())
                    return (1);
                return (0);
            }
			bool operator>=(const VectorIterator &other) const
			{
				if (this->ptr >= other.getptr())
					return (1);
                return (0);
			}
            bool operator>=(const VectorIterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                VectorIterator<T, true> ano = other;  
                if (this->ptr >= ano.getptr())
                    return (1);
                return (0);
            }
			bool operator<=(const VectorIterator &other) const
			{
				if (this->ptr <= other.getptr())
					return (1);
                return (0);
			}
            bool operator<=(const VectorIterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                VectorIterator<T, true> ano = other;  
                if (this->ptr <= ano.getptr())
                    return (1);
                return (0);
            }
            pointer getptr () const
            {
                return (ptr);
            }
        };
};




#endif