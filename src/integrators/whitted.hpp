#pragma once

#include "integrator.hpp"

namespace oingo::integrator
{

class whitted : public base
{
public:
    virtual void render(film::tile& t) final;

    std::size_t max_depth { 1 };

private:
    colour trace_ray(const RTCRay& ray);
};

}