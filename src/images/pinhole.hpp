#pragma once

#include "camera.hpp"

#include <Eigen/Core>

namespace oingo
{
    
struct pinhole : camera
{
    pinhole(Eigen::Vector3f pos, Eigen::Vector3f lookdir, Eigen::Vector3f updir, float fl);

    RTCRay generate_ray(const film::tile& t, std::size_t x, std::size_t y) const override;

    const Eigen::Vector3f pos, lookdir, updir, rightdir;
    const float fl;
};

}