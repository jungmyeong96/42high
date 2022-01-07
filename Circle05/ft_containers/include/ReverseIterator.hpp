#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "VectorIterator.hpp"

namespace ft
{
    template <class T, bool B>
    class reverse_iterator
    {
        public:
            typedef iterator_traits<T, B>               iterator_traits;
            typedef typename iterator_traits::value_type         value_type;
            typedef typename iterator_traits::reference          reference;
            typedef typename iterator_traits::pointer            pointer;
            typedef typename iterator_traits::difference_type    difference_type;
		private:
			pointer	ptr;

		public:
			reverse_iterator(void) : ptr(0) {}
			reverse_iterator(pointer ptr) : ptr(ptr) {};
			reverse_iterator(const reverse_iterator<T, false> &tmp): ptr(tmp.getptr()) {};
            explicit reverse_iterator(const VectorIterator<T, B>& copy) { ptr = copy.getptr(); } //reverse형에 iterator형넣기
			~reverse_iterator() {};
			VectorIterator<T, B> base() const { return this->ptr; };

            //Operator Assign
			reverse_iterator& operator=(const reverse_iterator &tmp)
			{
				if (this != &tmp)
					ptr = tmp.getptr();
				return (*this);
			}

			//Operator Access

            reference operator*() 
            { 
                pointer tmp;
                tmp = ptr;
                return (*--tmp); 
            }
            pointer operator->() { return (&operator*()); }
            reference operator[](int idx) const { return (*(*this + idx)); }

            //Plus Operation
            reverse_iterator operator+(int val) const
            {
                reverse_iterator tmp(*this);
                tmp.ptr -= val;
                return (tmp);
            }
            friend reverse_iterator operator+(difference_type n, const reverse_iterator<T, B>& x)
            {
                return reverse_iterator<T, B>(x.getptr() - n);
            }
            reverse_iterator &operator+=(int val)
            {
                this->ptr -= val;
                return (*this);
            }
            reverse_iterator operator++(int)//후위
            {
                reverse_iterator tmp(*this);
                --this->ptr;
                return (tmp);
            }
            reverse_iterator &operator++()//전위
            {
                --this->ptr;
                return (*this);
            }

            //Minus Operation
            reverse_iterator operator-(int val) const
            {
                reverse_iterator tmp(*this);
                tmp.ptr += val;
                return (tmp);
            }
            friend difference_type operator-(const reverse_iterator<T, B>& x, const reverse_iterator<T, B>& y)
            {
                return y.getptr() - x.getptr(); //비멤버를 멤버에 넣기위해 friend
            }
            reverse_iterator &operator-=(int val)
            {
                this->ptr += val;
                return (*this);
            }
            reverse_iterator operator--(int)
            {
                reverse_iterator tmp(*this);
                ++this->ptr;
                return(tmp);
            }
            reverse_iterator &operator--()
            {
                ++this->ptr;
                return (*this);
        	}

            //Operator compare 반대로해야하지않나? 체크해봐야함
            bool operator==(const reverse_iterator &other) const
            {
                if (this->ptr == other.getptr())
                    return (1);
                return (0);
            }
            bool operator==(const reverse_iterator<T, !B> &other) const
            {
                reverse_iterator<T, true> ano = other;  
                if (this->ptr == other.getptr())
                    return (1);
                return (0);
            }
            bool operator!=(const reverse_iterator &other) const
            {
                if (this->ptr != other.getptr())
                    return (1);
                return (0);
            }
            bool operator!=(const reverse_iterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                reverse_iterator<T, true> ano = other;  
                if (this->ptr != ano.getptr())
                    return (1);
                return (0);
            }
            bool operator>(const reverse_iterator &other) const
			{
				if (this->ptr < other.getptr())
					return (1);
				return (0);
			}
            bool operator>(const reverse_iterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                reverse_iterator<T, true> ano = other;  
                if (this->ptr < ano.getptr())
                    return (1);
                return (0);
            }
			bool operator<(const reverse_iterator &other) const
			{
				if (this->ptr > other.getptr())
					return (1);
                return (0);
			}
            bool operator<(const reverse_iterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                reverse_iterator<T, true> ano = other;  
                if (this->ptr > ano.getptr())
                    return (1);
                return (0);
            }
			bool operator>=(const reverse_iterator &other) const
			{
				if (this->ptr <= other.getptr())
					return (1);
                return (0);
			}
            bool operator>=(const reverse_iterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                reverse_iterator<T, true> ano = other;  
                if (this->ptr <= ano.getptr())
                    return (1);
                return (0);
            }
			bool operator<=(const reverse_iterator &other) const
			{
				if (this->ptr >= other.getptr())
					return (1);
                return (0);
			}
            bool operator<=(const reverse_iterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                reverse_iterator<T, true> ano = other;  
                if (this->ptr >= ano.getptr())
                    return (1);
                return (0);
            }
            pointer getptr () const
            {
                return (ptr);
            }
    };


}


#endif