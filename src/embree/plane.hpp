#pragma once

#include "geometry.hpp"

#include "Eigen/Core"

namespace oingo::embree
{

class plane : public geometry
{
public:
    plane(device& dev, const Eigen::Vector3f& norm, const Eigen::Vector3f& p, float size = 100000.0F);
};

}