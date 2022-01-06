#ifndef FT_HPP
#define FT_HPP

#include "Vector.hpp"
#include "Map.hpp"
#include "Stack.hpp"
#include <memory>

template <class T, class Alloc = std::allocator<T>>
class ft
{
    public:
        vector<T> vect();
};

#endif