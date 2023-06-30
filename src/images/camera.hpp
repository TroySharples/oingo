#pragma once

#include "film.hpp"

#include <embree3/rtcore_ray.h>

namespace oingo::camera
{

struct base
{
    virtual ~base() = default;

    virtual RTCRay generate_ray(const film::tile& t, std::size_t x, std::size_t y) const = 0;
};

}