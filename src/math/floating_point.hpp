#pragma once

#include <limits>

// Our own floating point type - sometimes our spacial operations need greater precision
#ifdef DOUBLE_PRECISION
using float_t = double;
#else
using float_t = float;
#endif

constexpr float_t ϵ = std::numeric_limits<float_t>::epsilon();