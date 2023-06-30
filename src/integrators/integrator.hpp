#pragma once

#include "images/camera.hpp"
#include "specular/lights.hpp"
#include "embree/scene.hpp"

#include <vector>
#include <memory>

namespace oingo::integrator
{

struct base
{
    virtual ~base() = default;
    
    std::unique_ptr<camera::base> cam;

    std::vector<lights::ambient> ambient_lights;
    std::vector<lights::point> point_lights;
    std::vector<lights::directional> directional_lights;
    
    embree::scene* scene;

    virtual void render(film::tile& t) = 0;
};

}