#pragma once

#include "math/vector.hpp"

namespace oingo
{

class film
{
public:
    film(std::size_t hori, std::size_t vert);

    const std::size_t horizontal_pixels;
    const std::size_t vertical_pixels;
};

}