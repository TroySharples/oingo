#pragma once

#include "lights.hpp"

#include "cameras/camera.hpp"
#include "objects/object.hpp"

#include <vector>

namespace oingo::scene
{

struct scene
{
    std::unique_ptr<cameras::camera> cam;

    std::vector<ambient_light> ambient_lights;
    std::vector<point_light> point_lights;
    std::vector<directional_light> directional_lights;

    std::vector<std::unique_ptr<objects::object>> objects;
};

}