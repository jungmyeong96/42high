#ifndef BASEITERATOR_HPP
# define BASEITERATOR_HPP

namespace ft
{
    template <class T>
    class BaseIterator
    {
        public:
            typedef T value_type;
            // typedef T* pointer;
            // typedef T const * const_pointer;
            // typedef T & reference;
            // typedef T const & const_reference;
            typedef std::ptrdiff_t difference_type;
        protected :
            T *ptr;
            
        public:
            BaseIterator() : ptr(0) {};
            BaseIterator(T *offset) : ptr(offset) {};
            BaseIterator(BaseIterator const &tmp) { *this = tmp; };
            virtual ~BaseIterator() {};

            //Operator assign
            BaseIterator &operator=(BaseIterator const &tmp)
            {
                if (this != &tmp)
                    this->ptr = tmp.ptr;
                return (*this);
            }

            //Operator Access
            // reference operator*() { return (*this->ptr); };
            // const_reference operator*() const { return (*this->ptr); };
            // pointer operator->() { return (this->ptr); };
            // const_pointer operator->() const { return (this->ptr); };
            // reference operator[](int idx) { return (*(this->ptr + idx)); };
            // const_reference operator[](int idx) const { return (*(this->ptr + idx)); };
            
            //Plus Operation
            BaseIterator operator+(int val) const
            {
                BaseIterator tmp(*this);
                return (tmp += val);
            }
            // BaseIterator &operator+=(int val)
            // {
            //     this->ptr += val;
            //     return (*this);
            // }
            BaseIterator operator++(int)
            {
                BaseIterator tmp(*this);
                this->ptr = this->ptr + 1;
                return (tmp);
            }
            BaseIterator &operator++()
            {
                this->ptr = this->ptr + 1;
                return (*this);
            }

            //Minus Operation
            BaseIterator operator-(int val) const
            {
                BaseIterator tmp(*this);
                return (tmp -= val);
            }
            difference_type operator-(BaseIterator const &other) const
            {
                return (this->ptr - other.ptr);
            }
            // BaseIterator &operator-=(int val)
            // {
            //     this->ptr = this->ptr - val;
            //     return (*this);
            // }
            BaseIterator operator--(int)
            {
                BaseIterator tmp(*this);
                this->ptr = this->ptr - 1;
                return(tmp);
            }
            BaseIterator &operator--()
            {
                this->ptr = this->ptr - 1;
                return (*this);
        	}


            //Operator compare
            bool operator==(const BaseIterator &other) const
            {
                if (this->ptr == other.ptr)
                    return (1);
                return (0);
            }
            bool operator!=(const BaseIterator &other) const
            {
                if (this->ptr != other.ptr)
                    return (1);
                return (0);
            }
            bool    operator>(const BaseIterator &other) const
			{
				if (this->ptr > other.ptr)
					return (1);
				return (0);
			}
			bool	operator<(const BaseIterator &other) const
			{
				if (this->ptr < other.ptr)
					return (1);
                return (0);
			}
			bool	operator>=(const BaseIterator &other) const
			{
				if (this->ptr >= other.ptr)
					return (1);
                return (0);
			}
			bool	operator<=(const BaseIterator &other) const
			{
				if (this->ptr <= other.ptr)
					return (1);
                return (0);
			}
            
        };

};




#endif