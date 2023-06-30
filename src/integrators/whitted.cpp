#include "whitted.hpp"

namespace oingo::integrator
{

void whitted::render(film::tile& t)
{
    for (std::size_t y = 0; y < t.get_height(); y++)
        for (std::size_t x = 0; x < t.get_width(); x++)
            t(x, y) = to_rgb(trace_ray(cam->generate_ray(t, x, y)));
}

colour whitted::trace_ray(const RTCRay& ray)
{
    return 0;
}

}