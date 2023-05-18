#pragma once

#include "integrator.hpp"

namespace integrator
{

class simple_sampler : integrator
{
public:
    void render(const scene::scene& s, const cameras::camera& c, std::ostream& os) override;
};

}