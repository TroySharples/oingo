#pragma once

#include "math/line.hpp"
#include "math/matrix.hpp"

namespace oingo
{

// Our own floating point type - sometimes our spacial operations need greater precision
#ifdef DOUBLE_PRECISION
using float_t = double;
#else
using float_t = float;
#endif

// Some useful geometric typedefs 
using ray_t       = math::line<float_t, 3>;
using spacial_t   = math::vector<float_t, 3>;
using transform_t = math::matrix<float_t,3, 3>;

// We define our bounding volumes with this
struct boundary
{
    spacial_t min;
    spacial_t max;
};

// We use plain-old floats for colour - we will never need double precision for this
using colour_t = math::vector<float, 3>;

}