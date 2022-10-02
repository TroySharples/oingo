#pragma once

#include "camera.hpp"

namespace oingo::cameras
{
    
struct pinhole : camera
{
    spacial_t position;
    spacial_t viewdir;
    spacial_t updir;
    float_t aspectratio;
    float_t fov;

    ray_t generate_ray(const film& f, std::size_t hori, std::size_t vert) override;
};

}