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
    // Make the intersect context
    RTCIntersectContext context;
    rtcInitIntersectContext(&context);
    context.flags = RTC_INTERSECT_CONTEXT_FLAG_COHERENT;

    // Make the ray and set the various options
    RTCRayHit rayhit { .ray {ray} };
    rayhit.hit.geomID = RTC_INVALID_GEOMETRY_ID;
    
    // Calculate if the ray hit any geometry in the scene
    rtcIntersect1(scene, &context, &rayhit);

    // Return black if it didn't hit anything
    if (rayhit.hit.geomID == RTC_INVALID_GEOMETRY_ID)
        return 0;

    // Otherwise return white for now - we'll do this properly later
    return 1;
}

}