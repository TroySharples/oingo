#include "simple_sampler.hpp"

#include "ppm.hpp"

namespace oingo::render
{

using rgb_t = rgb_t<std::uint8_t>;

static colour_t trace_ray(const scene::scene& s, const ray_t& ray)
{
    colour_t ret { 0 };

    // Calculate ambient light contribution
    for (const auto& light : s.ambient_lights)
        ret += light.colour;
        
    // Calculate object emmisive light contribution
    for (const auto& obj : s.objects)
        if (objects::intersection intersec; obj->hit(ray, intersec))
        {
            ret += intersec.mat.ke;
            break;
        }

    return ret;
}

void simple_sampler::render(const scene::scene& s, const film& f, std::ostream& os)
{
    ppm_write_header(os, f.horizontal_pixels, f.vertical_pixels, std::numeric_limits<rgb_t::value_type>::max());

    for (std::size_t j = 0; j < f.vertical_pixels; j++)
        for (std::size_t i = 0; i < f.horizontal_pixels; i++)
            ppm_write_pixel(os, to_rgb<std::uint8_t>(trace_ray(s, s.cam->generate_ray(f, i, j))));
}

}