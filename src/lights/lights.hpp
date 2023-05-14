#pragma once

#include "common.hpp"

namespace lights
{
    struct ambient_light
    {
        colour_t colour;
    };

    struct point_light
    {
        colour_t colour;
        spacial_t position;

        float constant_attenuation_coef  = 0;
        float linear_attenuation_coef    = 0;
        float quadratic_attenuation_coef = 1;

        float attenuate(float distance) const { return constant_attenuation_coef + distance * (linear_attenuation_coef + quadratic_attenuation_coef * distance); }
    };

    struct directional_light
    {
        colour_t colour;
        spacial_t direction;
    };

}