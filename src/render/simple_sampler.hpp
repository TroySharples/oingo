#pragma once

#include "renderer.hpp"

namespace oingo::render
{

class simple_sampler : renderer
{
public:
    void render(const scene::scene& s, const film& f, std::ostream& os) override;
};

}