#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
      template <class T>
    class ReverseIterator
    {
        public:
            typedef T value_type;
            typedef T* pointer;
            typedef T const * const_pointer;
            typedef T & reference;
            typedef T const & const_reference;
            typedef std::ptrdiff_t difference_type;
		private:
			pointer	ptr;

		public:
			ReverseIterator(void) : ptr(0) {}
			ReverseIterator(pointer ptr) : ptr(ptr) {};
			ReverseIterator(const ReverseIterator &tmp) : ptr(tmp.ptr) {};
			~ReverseIterator() {};
			
            //Operator Assign
			ReverseIterator& operator=(const ReverseIterator &tmp)
			{
				if (this != &tmp)
					ptr = tmp.ptr;
				return (*this);
			}

			//Operator Access
            reference operator*() { return (*this->ptr); }
            const_reference operator*() const { return (*this->ptr); }
            pointer operator->() { return (this->ptr); }
            const_pointer operator->() const { return (this->ptr); }
            reference operator[](int idx) { return (*(this->ptr - idx)); }
            const_reference operator[](int idx) const { return (*(this->ptr - idx)); }

            //Plus Operation
            ReverseIterator operator+(int val) const
            {
                ReverseIterator tmp(*this);
                return (tmp -= val);
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
                return (tmp += val);
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
            int operator==(const ReverseIterator &other) const
            {
                if (this->ptr == other.ptr)
                    return (1);
                return (0);
            }
            int operator!=(const ReverseIterator &other) const
            {
                if (this->ptr != other.ptr)
                    return (1);
                return (0);
            }
            int	operator>(const ReverseIterator &other) const
			{
				if (this->ptr > other.ptr)
					return (1);
				return (0);
			}
			int	operator<(const ReverseIterator &other) const
			{
				if (this->ptr < other.ptr)
					return (1);
                return (0);
			}
			int	operator>=(const ReverseIterator &other) const
			{
				if (this->ptr >= other.ptr)
					return (1);
                return (0);
			}
			int	operator<=(const ReverseIterator &other) const
			{
				if (this->ptr <= other.ptr)
					return (1);
                return (0);
			}
    };


}


#endif