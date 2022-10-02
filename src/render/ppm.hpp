#pragma once

#include "common.hpp"

#include <iostream>

namespace oingo::render
{

std::ostream& ppm_write_header(std::ostream& os, std::size_t horizontal_pixels, std::size_t vertical_pixels, std::size_t bits = std::numeric_limits<std::uint8_t>::max())
{
    return os << "P3\n" << horizontal_pixels << " " << vertical_pixels << '\n' << bits << '\n';
}

template <typename T>
std::ostream& ppm_write_pixel(std::ostream& os, const rgb_t<T>& pixel)
{
    return os << pixel << '\n';
}

}