#pragma once

#include "geometry.hpp"

#include "Eigen/Core"

namespace oingo::embree
{

class plane : public geometry
{
public:
    plane(device& dev, const Eigen::Vector3f& point, const Eigen::Vector3f& normal);
};

}