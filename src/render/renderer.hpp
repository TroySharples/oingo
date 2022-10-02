#pragma once

#include "scene/scene.hpp"

namespace oingo::render
{

struct renderer
{
    virtual void(const scene& s, const film& f, std::ostream& os) = 0;
};

}