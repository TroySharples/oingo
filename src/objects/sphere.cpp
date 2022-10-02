#include "sphere.hpp"

namespace oingo::objects
{

bool sphere::hit(const ray_t& ray) const
{
    const auto oc = ray.origin - _centre;
    const auto a = math::square_length(ray.direction);
    const auto b = 2 * math::dot_product(oc, ray.direction);
    const auto c = math::square_length(oc) - std::pow(_radius, 2);
    const auto discriminant = std::pow(b, 2) - 4*a*c;

    return discriminant > epsilon;
}

bool sphere::hit(const ray_t& ray, intersection& intersec) const
{
    // Will fill out the ray structure eventually
    return hit(ray);
}

boundary sphere::get_boundary() const
{
    const spacial_t diagonal = { _radius, _radius, _radius };
    return { _centre - diagonal, _centre + diagonal };
}

void sphere::translate(const spacial_t& t)
{
    _centre += t;
}

void sphere::scale(const spacial_t& s)
{
    if (s[0] != s[1] || s[0] !=  s[2])
        throw std::runtime_error("Spheres only support proportional scaling");
    
    _radius *= s[0];
}

void sphere::rotate(const spacial_t& axis, float_t rad)
{
    // Sphere's don't change when rotated. Note that this will no longer be the case if we ever decide to support nonproportional scaling    
}

}