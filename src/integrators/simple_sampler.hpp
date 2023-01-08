#pragma once

#include "integrator.hpp"

namespace oingo::integrator
{

class simple_sampler : integrator
{
public:
    void render(const scene::scene& s, const cameras::film& f, std::ostream& os) override;
};

}