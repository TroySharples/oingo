#pragma once

#include "scene/scene.hpp"
#include "cameras/film.hpp"

#include <iostream>

namespace integrator
{

struct integrator
{
    virtual ~integrator() = default;

    virtual void render(const scene::scene& s, const cameras::film& f, std::ostream& os) = 0;
};

}