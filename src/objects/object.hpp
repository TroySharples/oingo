#pragma once

#include "surface.hpp"

namespace oingo::objects
{

class object
{
public:
    virtual ~object() = default;

    virtual bool hit(const ray_t& ray) = 0;
    virtual bool hit(const ray_t& ray, intersection& intersec) = 0;

    material mat;

private:    
    spacial_t _centre = { 0, 0, 0};


};

}