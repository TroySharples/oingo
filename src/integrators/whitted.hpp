#pragma once

#include "integrator.hpp"

namespace oingo::integrator
{

class whitted : public base
{
public:
    void render(film::tile& t) final;

private:
    colour trace_ray(const RTCRay& ray);
};

}