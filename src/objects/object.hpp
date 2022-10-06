#pragma once

#include "surface.hpp"

#include <memory>

namespace oingo::objects
{

struct object
{
    virtual ~object() = default;

    virtual std::unique_ptr<object> clone() const = 0;

    virtual bool hit(const ray_t& ray) const = 0;
    virtual bool hit(const ray_t& ray, intersection& intersec) const = 0;

    material mat;
    
    virtual boundary get_boundary() const = 0;

    virtual void translate(const spacial_t& t) = 0;
    virtual void scale(const spacial_t& s) = 0;
    virtual void rotate(const spacial_t& axis, float_t rad) = 0;
};

}