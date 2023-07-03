#pragma once

#include "camera.hpp"

#include <Eigen/Core>

namespace oingo::camera
{
    
struct pinhole : base
{
    pinhole(Eigen::Vector3f pos_, Eigen::Vector3f lookdir_, Eigen::Vector3f updir_, float fl_);

    RTCRay generate_ray(const film::tile& t, std::size_t x, std::size_t y) const override;

    const Eigen::Vector3f pos, lookdir, updir, rightdir;
    const float fl;
};

}