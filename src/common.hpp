#pragma once

#include "math/line.hpp"
#include "math/matrix.hpp"

#include <limits>

namespace oingo
{

// Our own floating point type - sometimes our spacial operations need greater precision
#ifdef DOUBLE_PRECISION
using float_t = double;
#else
using float_t = float;
#endif

constexpr float_t epsilon = std::numeric_limits<float_t>::epsilon();

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

// The actual RBG values of the pixels. We template for optional 8-bit / 16-bit colour
template <typename T = std::uint8_t>
requires std::same_as<T, std::uint8_t> || std::same_as<T, std::uint16_t>
using rgb_t = math::vector<T, 3>;

using rgb8_t  = rgb_t<std::uint8_t>;
using rgb16_t = rgb_t<std::uint16_t>;

// Converts a floating point colour to its corresponding RGB value. Floating point values over 1 are truncated
template <typename T = std::uint8_t>
constexpr rgb_t<T> to_rgb(const colour_t& colour)
{
    rgb_t<T> ret;
    for (std::size_t i = 0; i < 3; i++)
        ret[i] = std::round(std::min(std::abs(colour[i]), 1.0f) * std::numeric_limits<T>::max());
    return ret;
}

}