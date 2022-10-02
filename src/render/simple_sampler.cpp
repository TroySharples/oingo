#include "simple_sampler.hpp"

#include "ppm.hpp"

namespace oingo::render
{

using rgb_t = rgb_t<std::uint8_t>;

void simple_sampler::render(const scene::scene& s, const film& f, std::ostream& os)
{
    ppm_write_header(os, f.horizontal_pixels, f.vertical_pixels, std::numeric_limits<rgb_t::value_type>::max());

    for (std::size_t j = 0; j < f.vertical_pixels; j++)
        for (std::size_t i = 0; i < f.horizontal_pixels; i++)
        {
            const ray_t ray = s.cam->generate_ray(f, i, j);
            rgb_t pixel = { 0 };

            for (const auto& obj : s.objects)
                if (objects::intersection intersec; obj->hit(ray, intersec))
                {
                    pixel = to_rgb(intersec.mat.ke);
                    break;   
                }

            ppm_write_pixel(os, pixel);
        }
}

}