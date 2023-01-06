#pragma once

#include "film.hpp"
#include "common.hpp"

namespace oingo::cameras
{

struct camera
{
    virtual ~camera() = default;
    virtual ray_t generate_ray(const film& f, std::size_t hori, std::size_t vert) = 0;
};

}