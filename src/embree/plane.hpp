#pragma once

#include "geometry.hpp"

#include "Eigen/Core"
#include <Eigen/src/Core/Matrix.h>

namespace oingo::embree
{

class plane : public geometry
{
public:
    plane(device& dev, Eigen::Vector3f norm, float l);

    const Eigen::Vector3f norm;
    const float l;
};

}