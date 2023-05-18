#pragma once

#include "scene/scene.hpp"
#include "cameras/camera.hpp"

#include <iostream>

namespace integrator
{

struct integrator
{
    virtual ~integrator() = default;

    virtual void render(const scene::scene& s, const cameras::camera& c, std::ostream& os) = 0;
};

}