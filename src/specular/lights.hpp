#pragma once

#include "colour.hpp"

#include <Eigen/Core>

namespace oingo::lights
{

struct ambient
{
    colour col;
};

struct point
{
    colour col;
    Eigen::Vector3f pos;

    float constant_attenuation_coef  {1.0F};
    float linear_attenuation_coef    {0.0F};
    float quadratic_attenuation_coef {0.0F};
};

struct directional
{
    colour col;
    Eigen::Vector3f dir;
};

}