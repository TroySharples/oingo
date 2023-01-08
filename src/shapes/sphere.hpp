#pragma once

#include "shape.hpp"

namespace oingo::shapes
{

class sphere : public shape
{
public:
    virtual ~sphere() = default;

    std::unique_ptr<shape> clone() const override { return std::make_unique<sphere>(*this); }

    bool hit(const ray_t& ray) const override;
    bool hit(const ray_t& ray, intersection& intersec) const override;

    boundary get_boundary() const override;
};

}