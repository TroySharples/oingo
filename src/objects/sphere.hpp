#pragma once

#include "object.hpp"

namespace oingo::objects
{

class sphere : public object
{
public:
    virtual ~sphere() = default;

    bool hit(const ray_t& ray) const override;
    bool hit(const ray_t& ray, intersection& intersec) const override;

    boundary get_boundary() const override;

    void translate(const spacial_t& t) override;
    void scale(const spacial_t& s) override;
    void rotate(const spacial_t& axis, float_t rad) override;

private:
    spacial_t _centre = { 0 };
    float_t _radius = 1;
};

}