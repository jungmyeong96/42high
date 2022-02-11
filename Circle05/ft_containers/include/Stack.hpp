#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template < typename T , typename Container = ft::vector<T> >
    class stack
    {
        public:
            typedef T value_type;
            typedef Container   container_type;
            typedef typename container_type::reference       reference;
            typedef typename container_type::const_reference const_reference;
            typedef typename container_type::size_type       size_type;
        
        protected:
            container_type ctnr;


        public:
            //Canonical form
            explicit stack (const container_type& ctnr = container_type()) : ctnr(ctnr) {};
            stack(const stack& other) : ctnr(other.ctnr) {};
            stack& operator=(const stack& other) { ctnr = other.ctnr; return (*this); };
            ~stack() {};

            //Member function
            bool empty() const                  { return (ctnr.empty()); };
            size_type size() const              { return (ctnr.size()); };
            reference top()                     { return (ctnr.back()); };
            const_reference top() const         { return (ctnr.back()); };
            void push(const value_type& val)    { ctnr.push_back(val); };
            void pop()                          { ctnr.pop_back(); };

            friend bool operator==(const stack& lhs, const stack& rhs)  { return lhs.ctnr == rhs.ctnr; };
            friend bool operator!=(const stack& lhs, const stack& rhs)  { return lhs.ctnr != rhs.ctnr; };
            friend bool operator<(const stack& lhs, const stack& rhs)   { return lhs.ctnr < rhs.ctnr; };
            friend bool operator<=(const stack& lhs, const stack& rhs)  { return lhs.ctnr <= rhs.ctnr; };
            friend bool operator>(const stack& lhs, const stack& rhs)   { return lhs.ctnr > rhs.ctnr; };
            friend bool operator>=(const stack& lhs, const stack& rhs)  { return lhs.ctnr >= rhs.ctnr; };
    };
}

#endif