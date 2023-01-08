#include "simple_sampler.hpp"

#include "ppm.hpp"

namespace oingo::integrator
{

static colour_t trace_ray(const scene::scene& s, const ray_t& ray)
{
    colour_t ret { 0 };

    // // Calculate ambient light contribution
    // for (const auto& light : s.ambient_lights)
    //     ret += light.colour;

    // // Calculate the directional light contribution
    // for (const auto& light : s.directional_lights)
    // {
    //     // Is the light near where this ray is looking? If it is behind the ray we exit here without further computation
    //     const float_t alignment = math::dot_product(light.direction, ray.direction);
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
    //     const float_t alignment = math::dot_product(direction, ray.direction);
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
    //         const float_t distance = math::length(direction);
    //         const float_t alignment = math::dot_product(ray.direction, direction) / distance;
    //         ret += light.colour * alignment / light.attenuate(distance);
    //     }
    // }
        
    // // Calculate shape emmisive light contribution
    // std::optional<objects::intersection> nearest_intersec;
    // for (const auto& obj : s.objects)
    //     if (objects::intersection intersec; obj->hit(ray, intersec) && (!nearest_intersec.has_value() || nearest_intersec.value().distance > intersec.distance))
    //         nearest_intersec = intersec;
    // if (nearest_intersec.has_value())
    // {
    //     const ray_t reflection = { .origin = nearest_intersec.value().position, .direction = ray.direction + 2*nearest_intersec.value().normal };
    //     ret += (nearest_intersec.value().mat.ke + nearest_intersec.value().mat.ks * trace_ray(s, reflection)) * nearest_intersec.value().alignment / (1 + std::pow(nearest_intersec.value().distance, 2));
    // }

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