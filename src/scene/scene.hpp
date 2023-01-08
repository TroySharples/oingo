#pragma once

#include "object.hpp"

#include "lights/lights.hpp"
#include "cameras/camera.hpp"

#include <vector>

namespace oingo::scene
{

struct scene
{
    std::vector<object> objects;

    std::unique_ptr<cameras::camera> cam;

    std::vector<lights::ambient_light> ambient_lights;
    std::vector<lights::point_light> point_lights;
    std::vector<lights::directional_light> directional_lights;
};

}