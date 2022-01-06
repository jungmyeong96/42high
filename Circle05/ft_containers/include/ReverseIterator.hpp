#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "VectorIterator.hpp"

namespace ft
{
      template <class T, bool B>
    class ReverseIterator
    {
        public:
            typedef T value_type;
            typedef typename ChooseConst<B, T&, const T&>::type     reference;
            typedef typename ChooseConst<B, T*, const T*>::type     pointer;
            typedef std::ptrdiff_t difference_type;
		private:
			pointer	ptr;

		public:
			ReverseIterator(void) : ptr(0) {}
			ReverseIterator(pointer ptr) : ptr(ptr) {};
			ReverseIterator(const ReverseIterator<T, false> &tmp): ptr(tmp.getptr()) {};
            explicit ReverseIterator(const VectorIterator<T, B>& copy) { ptr = copy.getptr(); } //reverse형에 iterator형넣기
			~ReverseIterator() {};
			VectorIterator<T, B> base() const { return this->ptr; };

            //Operator Assign
			ReverseIterator& operator=(const ReverseIterator &tmp)
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
            ReverseIterator operator+(int val) const
            {
                ReverseIterator tmp(*this);
                tmp.ptr -= val;
                return (tmp);
            }
            friend ReverseIterator operator+(difference_type n, const ReverseIterator<T, B>& x)
            {
                return ReverseIterator<T, B>(x.ptr - n);
            }
            ReverseIterator &operator+=(int val)
            {
                this->ptr -= val;
                return (*this);
            }
            ReverseIterator operator++(int)//후위
            {
                ReverseIterator tmp(*this);
                --this->ptr;
                return (tmp);
            }
            ReverseIterator &operator++()//전위
            {
                --this->ptr;
                return (*this);
            }

            //Minus Operation
            ReverseIterator operator-(int val) const
            {
                ReverseIterator tmp(*this);
                tmp.ptr += val;
                return (tmp);
            }
            friend difference_type operator-(const ReverseIterator<T, B>& x, const ReverseIterator<T, B>& y)
            {
                return y.ptr - x.ptr; //비멤버를 멤버에 넣기위해 friend
            }
            ReverseIterator &operator-=(int val)
            {
                this->ptr += val;
                return (*this);
            }
            ReverseIterator operator--(int)
            {
                ReverseIterator tmp(*this);
                ++this->ptr;
                return(tmp);
            }
            ReverseIterator &operator--()
            {
                ++this->ptr;
                return (*this);
        	}

            //Operator compare 반대로해야하지않나? 체크해봐야함
            bool operator==(const ReverseIterator &other) const
            {
                if (this->ptr == other.getptr())
                    return (1);
                return (0);
            }
            bool operator==(const ReverseIterator<T, !B> &other) const
            {
                ReverseIterator<T, true> ano = other;  
                if (this->ptr == other.getptr())
                    return (1);
                return (0);
            }
            bool operator!=(const ReverseIterator &other) const
            {
                if (this->ptr != other.getptr())
                    return (1);
                return (0);
            }
            bool operator!=(const ReverseIterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                ReverseIterator<T, true> ano = other;  
                if (this->ptr != ano.getptr())
                    return (1);
                return (0);
            }
            bool operator>(const ReverseIterator &other) const
			{
				if (this->ptr < other.getptr())
					return (1);
				return (0);
			}
            bool operator>(const ReverseIterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                ReverseIterator<T, true> ano = other;  
                if (this->ptr < ano.getptr())
                    return (1);
                return (0);
            }
			bool operator<(const ReverseIterator &other) const
			{
				if (this->ptr > other.getptr())
					return (1);
                return (0);
			}
            bool operator<(const ReverseIterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                ReverseIterator<T, true> ano = other;  
                if (this->ptr > ano.getptr())
                    return (1);
                return (0);
            }
			bool operator>=(const ReverseIterator &other) const
			{
				if (this->ptr <= other.getptr())
					return (1);
                return (0);
			}
            bool operator>=(const ReverseIterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                ReverseIterator<T, true> ano = other;  
                if (this->ptr <= ano.getptr())
                    return (1);
                return (0);
            }
			bool operator<=(const ReverseIterator &other) const
			{
				if (this->ptr >= other.getptr())
					return (1);
                return (0);
			}
            bool operator<=(const ReverseIterator<T, !B> &other) const // const랑 non const비교할 경우 처리
            {
                ReverseIterator<T, true> ano = other;  
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