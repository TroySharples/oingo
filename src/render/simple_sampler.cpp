#include "simple_sampler.hpp"

namespace oingo::render
{

using rgb_t = rgb_t<std::uint8_t>;

void simple_sampler::render(const scene::scene& s, const film& f, std::ostream& os)
{
    os << "P3\n" << f.horizontal_pixels << " " << f.vertical_pixels << '\n' << static_cast<int>(std::numeric_limits<rgb_t::value_type>::max()) << '\n';

    for (std::size_t i = 0; i < f.horizontal_pixels; i++)
        for (std::size_t j = 0; j < f.vertical_pixels; j++)
        {
            const ray_t ray = s.cam->generate_ray(f, i, j);

            rgb_t pixel = { 0, 0, 0 };
            for (const auto& obj : s.objects)
                if (obj->hit(ray))
                {
                    pixel = { std::numeric_limits<rgb_t::value_type>::max(), 0, 0 };
                    break;   
                }

            os << pixel << '\n';
        }
}

}