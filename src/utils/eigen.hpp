#pragma once

#include <Eigen/Core>

namespace oingo::eigen
{

// Parameters are in degrees (not radians) 
Eigen::Matrix3f make_rotation(float x, float y, float z);

}