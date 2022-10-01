#pragma once

#include "math/line.hpp"
#include "math/matrix.hpp"

namespace oingo
{

#ifdef DOUBLE_PRECISION
using float_t = double;
#else
using float_t = float;
#endif

using ray_t       = math::line<float_t, 3>;
using spacial_t   = math::vector<float_t, 3>;
using transform_t = math::matrix<float_t,3, 3>;

struct boundary
{
    spacial_t min;
    spacial_t max;
};

}