#pragma once

#include <memory>

#include "materials/material.hpp"
#include "shapes/shape.hpp"

#include "common.hpp"

namespace oingo::scene
{

    struct object
    {
        std::unique_ptr<shapes::shape> shp;
        spacial_t pos = { 0, 0, 0 };
        transform_t trans = math::identity<float_t, 3>();
        materials::material mat;
    };

}