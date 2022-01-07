#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"

namespace ft
{
    template < typename T , typename Container = ft::Vector<T> >
    class Stack
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
            explicit Stack (const container_type& ctnr = container_type()) : ctnr(ctnr) {};
            //컨테이너 어댑터는 내부적으로 컨테이너 개체를 데이터로 유지합니다. 이 컨테이너 개체는 생성자에 전달 된 ctnr 인수 의 복사본입니다(있는 경우). 그렇지 않으면 빈 컨테이너입니다.
            Stack(const Stack& other) : ctnr(other.ctnr) {};
            Stack& operator=(const Stack& other) { ctnr = other.ctnr; return (*this); };
            ~Stack() {};

            //Member function
            bool empty() const                  { return (ctnr.empty()); };
            size_type size() const              { return (ctnr.size()); };
            reference top()                     { return (ctnr.back()); };
            const_reference top() const         { return (ctnr.back()); };
            void push(const value_type& val)    { ctnr.push_back(val); };
            void pop()                          { ctnr.pop_back(); };

            friend bool operator==(const Stack& lhs, const Stack& rhs)  { return lhs.ctnr == rhs.ctnr; };
            friend bool operator!=(const Stack& lhs, const Stack& rhs)  { return lhs.ctnr != rhs.ctnr; };
            friend bool operator<(const Stack& lhs, const Stack& rhs)   { return lhs.ctnr < rhs.ctnr; };
            friend bool operator<=(const Stack& lhs, const Stack& rhs)  { return lhs.ctnr <= rhs.ctnr; };
            friend bool operator>(const Stack& lhs, const Stack& rhs)   { return lhs.ctnr > rhs.ctnr; };
            friend bool operator>=(const Stack& lhs, const Stack& rhs)  { return lhs.ctnr >= rhs.ctnr; };
    };
}

#endif