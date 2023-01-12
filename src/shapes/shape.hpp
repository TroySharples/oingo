#pragma once

#include "common.hpp"

#include <memory>

namespace oingo::shapes
{

struct shape
{
    virtual ~shape() = default;

    virtual std::unique_ptr<shape> clone() const = 0;

    struct intersection
    {
        floating_point_t t;
        spacial_t n;
    };

    virtual bool hit(const ray_t& ray) const = 0;
    virtual bool hit(const ray_t& ray, intersection& intersec) const = 0;
    
    virtual boundary get_boundary() const = 0;
};

}