#include "simple_sampler.hpp"

#include "ppm.hpp"

namespace oingo::integrator
{

static colour_t trace_ray(const scene::scene& s, const ray_t& ray)
{
    colour_t ret { 0 };

    // Calculate ambient light contribution
    for (const auto& light : s.ambient_lights)
        ret += light.colour;

    // // Calculate the directional light contribution
    // for (const auto& light : s.directional_lights)
    // {
    //     // Is the light near where this ray is looking? If it is behind the ray we exit here without further computation
    //     const floating_point_t alignment = math::dot_product(light.direction, ray.direction);
    //     if (alignment < ϵ)
    //         continue;
    
    //     // Is a shape casting a shadow on this light?
    //     const ray_t shadow_ray { .origin = ray.origin, .direction = light.direction };
    //     bool hit = true;
    //     for (const auto& obj : s.objects)
    //         if (obj->shape->hit(shadow_ray))
    //         {
    //             hit = false;
    //             break;
    //         }

    //     // Add the illumination affect if it hit
    //     if (hit)
    //         ret += light.colour * alignment;
    // }

    // // Calculate the point light contribution
    // for (const auto& light : s.point_lights)
    // {
    //     // Calculates the direction of this light
    //     const spacial_t direction = math::normalise(light.position - ray.origin);

    //     // Is the light near where this ray is looking? If it is behind the ray we exit here without further computation
    //     const floating_point_t alignment = math::dot_product(direction, ray.direction);
    //     if (alignment < ϵ)
    //         continue;
    
    //     // Is an shape casting a shadow on this light?
    //     const ray_t shadow_ray { .origin = ray.origin, .direction = direction };
    //     bool hit = true;
    //     for (const auto& obj : s.objects)
    //         if (obj->hit(shadow_ray))
    //         {
    //             hit = false;
    //             break;
    //         }

    //     // Add the attenuation if it hit
    //     if (hit)
    //     {
    //         const floating_point_t distance = math::length(direction);
    //         const floating_point_t alignment = math::dot_product(ray.direction, direction) / distance;
    //         ret += light.colour * alignment / light.attenuate(distance);
    //     }
    // }
        
    // Calculate shape emmisive light contribution
    std::optional<shapes::shape::intersection> nearest_intersec;
    materials::material mat;
    for (const auto& obj : s.objects)
    {
        const ray_t transformed_ray = {
            .origin    = math::invert(obj.trans) * (ray.origin - obj.pos),
            .direction = (math::invert(obj.trans) * ray.direction).normalise()
        };
        if (shapes::shape::intersection intersec; obj.shp->hit(transformed_ray, intersec) && (!nearest_intersec.has_value() || nearest_intersec.value().t > intersec.t))
        {
            nearest_intersec = { .t = intersec.t, .n = math::invert(math::transpose(obj.trans)) * intersec.n };
            mat = obj.mat;
        }
    }
    if (nearest_intersec.has_value())
    {
        nearest_intersec.value().n.normalise();
        ret += mat.ke * std::abs(math::dot_product(nearest_intersec.value().n, ray.direction));// / (1 + std::pow(nearest_intersec.value().t, 2));
    }

    return ret;
}

void simple_sampler::render(const scene::scene& s, const cameras::film& f, std::ostream& os)
{
    ppm_write_header(os, f.horizontal_pixels, f.vertical_pixels, std::numeric_limits<rgb8_t::value_type>::max());

    for (std::size_t j = 0; j < f.vertical_pixels; j++)
        for (std::size_t i = 0; i < f.horizontal_pixels; i++)
            ppm_write_pixel(os, to_rgb<std::uint8_t>(trace_ray(s, s.cam->generate_ray(f, i, j))));
}

}