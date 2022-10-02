#pragma once

#include "camera.hpp"
#include "lights.hpp"

#include "objects/object.hpp"

#include <vector>
#include <memory>

namespace oingo::scene
{

struct scene
{
    camera cam;

    std::vector<ambient_light> ambient_lights;
    std::vector<point_light> point_lights;
    std::vector<directional_light> directional_lights;

    std::vector<std::unique_ptr<objects>> objects;
};

}