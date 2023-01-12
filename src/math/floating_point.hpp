#pragma once

#include <limits>

// Our own floating point type - sometimes our spacial operations need greater precision
#ifdef DOUBLE_PRECISION
using floating_point_t = double;
#else
using floating_point_t = float;
#endif

constexpr floating_point_t ϵ = std::numeric_limits<floating_point_t>::epsilon();