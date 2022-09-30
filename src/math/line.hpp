#pragma once

#include "vector.hpp"

namespace oingo::math
{

template <typename T, std::size_t S>
struct line
{
    using spacial_t = vector<_T, _S>;

    spacial_t operator[](const T& t) const { return origin + t*direction; }

    spacial_t origin;
    spacial_t direction;
};

}