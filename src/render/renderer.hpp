#pragma once

#include "scene/scene.hpp"

#include "film.hpp"

#include <iostream>

namespace oingo::render
{

struct renderer
{
    virtual ~renderer() = default;

    virtual void render(const scene::scene& s, const film& f, std::ostream& os) = 0;
};

}