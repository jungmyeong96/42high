#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

namespace ft
{
    template <class T>
    class VectorIterator
    {
        public:
            typedef T value_type;
            typedef T* pointer;
            typedef T const * const_pointer;
            typedef T & reference;
            typedef T const & const_reference;
            typedef std::ptrdiff_t difference_type;
        private :
            pointer ptr;
        public:
            VectorIterator() : ptr(0) {};
            VectorIterator(pointer offset) : ptr(offset) {};
            VectorIterator(VectorIterator const &tmp): ptr(tmp.ptr) {};
            virtual ~VectorIterator() {};

            //Operator assign
            VectorIterator &operator=(VectorIterator const &tmp)
            {
                if (this != &tmp)
                    this->ptr = tmp.ptr;
                return (*this);
            }

            //Operator Access
            reference operator*() { return (*this->ptr); };
            const_reference operator*() const { return (*this->ptr); };
            pointer operator->() { return (this->ptr); };
            const_pointer operator->() const { return (this->ptr); };
            reference operator[](int idx) { return (*(this->ptr + idx)); };
            const_reference operator[](int idx) const { return (*(this->ptr + idx)); };
            
            //Plus Operation
            VectorIterator operator+(int val) const
            {
                VectorIterator tmp(*this);
                return (tmp += val);
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
            int operator==(const VectorIterator &other) const
            {
                if (this->ptr == other.ptr)
                    return (1);
                return (0);
            }
            int operator!=(const VectorIterator &other) const
            {
                if (this->ptr != other.ptr)
                    return (1);
                return (0);
            }
            int	operator>(const VectorIterator &other) const
			{
				if (this->ptr > other.ptr)
					return (1);
				return (0);
			}
			int	operator<(const VectorIterator &other) const
			{
				if (this->ptr < other.ptr)
					return (1);
                return (0);
			}
			int	operator>=(const VectorIterator &other) const
			{
				if (this->ptr >= other.ptr)
					return (1);
                return (0);
			}
			int	operator<=(const VectorIterator &other) const
			{
				if (this->ptr <= other.ptr)
					return (1);
                return (0);
			}



        };
};

#endif