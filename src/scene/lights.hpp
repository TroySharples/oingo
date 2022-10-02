#pragma once

#include "common.hpp"

namespace oingo::scene
{
    struct ambient_light
    {
        colour_t colour;
    };

    struct point_light
    {
        colour_t colour;
        spacial_t position;

        float constant_attenuation_coef;
        float linear_attenuation_coef;
        float quadratic_attenuation_coef;
    };

    struct directional_light
    {
        colour_t colour;
        spacial_t direction;
    };

}