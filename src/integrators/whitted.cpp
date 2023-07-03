#include "whitted.hpp"

#include "specular/material.hpp"
#include "embree/helper.hpp"
#include "utils/depth_counter.hpp"

namespace oingo::integrator
{

// A simple Lambertian shader. The check that norm_dot_light > 0 is not dont here and should be done before calling
// this function.
static colour lambert_diffusive_shader(const material& mat, float norm_dot_light)
{
    return mat.kd * norm_dot_light;
}

// A simple Phong shader. There is no contribution for reflections that are facing away from the light
static colour phong_specular_shader(const material& mat, float refl_dot_light)
{
    return mat.ks * std::pow(std::max(0.0F, refl_dot_light), mat.shininess);
}

// Calculates the minimum distance the ray cast should work for to avoid self intersection. Note the scalar value
// is arbitary - will experiment to see what looks good
static float calculate_tnear(float norm_dot_dir)
{
    return 0.5F;
    constexpr float tnear_scalar = 0.5F;
    return tnear_scalar / norm_dot_dir;
}

void whitted::render(film::tile& t)
{
    for (std::size_t y = 0; y < t.get_height(); y++)
        for (std::size_t x = 0; x < t.get_width(); x++)
            t(x, y) = to_rgb(trace_ray(cam->generate_ray(t, x, y)));
}

colour whitted::trace_ray(const RTCRay& ray)
{
    colour ret { 0.0F };

    // *************************************************************************************************************
    // INITIAL RAY INTERSECTION WITH GEOMETRY
    // 
    // This is the first ray intersection with the geometry. We need to calculate the intersection point, the normal
    // at the intersection point, and the reflection direction. We also retrieve the material of the intersected
    // geometry.
    // *************************************************************************************************************

    // Make the intersect context
    RTCIntersectContext context_ray;
    rtcInitIntersectContext(&context_ray);
    context_ray.flags = RTC_INTERSECT_CONTEXT_FLAG_COHERENT;

    // Make the ray and set the various options
    RTCRayHit rayhit { .ray {ray} };
    rayhit.hit.geomID = RTC_INVALID_GEOMETRY_ID;
    
    // Calculate if the ray hit any geometry in the scene
    rtcIntersect1(scene, &context_ray, &rayhit);

    // Return black if it didn't hit anything
    if (rayhit.hit.geomID == RTC_INVALID_GEOMETRY_ID)
        return ret;

    const RTCGeometry geom = rtcGetGeometry(scene, rayhit.hit.geomID);

    const Eigen::Vector3f ray_dir  = Eigen::Vector3f{ rayhit.ray.dir_x, rayhit.ray.dir_y, rayhit.ray.dir_z };
    const Eigen::Vector3f cam_pos  = Eigen::Vector3f{ rayhit.ray.org_x, rayhit.ray.org_y, rayhit.ray.org_z };
    const Eigen::Vector3f hit_pos  = cam_pos + rayhit.ray.tfar * ray_dir;
    const Eigen::Vector3f norm_dir = embree::get_interpolated_normal(geom, rayhit.hit);
    const Eigen::Vector3f refl_dir = (ray_dir - 2 * ray_dir.dot(norm_dir) * norm_dir).normalized();
    
    const float norm_dot_refl = norm_dir.dot(refl_dir); 

    const material& mat = *static_cast<material*>(rtcGetGeometryUserData(geom));
    
    // *************************************************************************************************************
    // LIGHTING
    // 
    // This calculates the various lighting effects on the material. This includes the emmissive lighting of the
    // material, the ambient lighting, the directional lighting, and the point lighting. We cast shaddow rays to
    // determine if the point is in shadow or not. The minimum intersection distance depends on how shallow the
    // angle of the light is to the surface to prevent self-intersection.
    // *************************************************************************************************************

    // Emmissive lighting of the material
    ret += mat.ke;

    // Ambient light contributions
    for (const auto& light : ambient_lights)
        ret += mat.ka * light.col;

    // Directional light contributions
    for (const auto& light : directional_lights)
    {
        // Return immediately if the light is facing away from the surface
        const float norm_dot_light = norm_dir.dot(light.dir);
        if (norm_dot_light < 0)
            continue;

        // Cast the shadow ray
        RTCRay shadow_ray = embree::make_ray(hit_pos, light.dir, calculate_tnear(norm_dot_light));

        RTCIntersectContext context_shadow;
        rtcInitIntersectContext(&context_shadow);
        rtcOccluded1(scene, &context_shadow, &shadow_ray);

        // We only have specualar and diffuse components if the shadow ray didn't hit anything
        if (shadow_ray.tfar > 0)
            ret += light.col * (lambert_diffusive_shader(mat, norm_dot_light) + phong_specular_shader(mat, refl_dir.dot(light.dir)));
    }

    // Point light contributions
    for (const auto& light : point_lights)
    {
        // Calculate the light direction and distance (more efficient to calculate the norm first so we don't have to do the square-root twice)
        const float tfar = (light.pos - hit_pos).norm();
        const Eigen::Vector3f light_dir = (light.pos - hit_pos) / tfar;

        // Return immediately if the light is facing away from the surface
        const float norm_dot_light = norm_dir.dot(light_dir);
        if (norm_dot_light < 0)
            continue;

        // Cast the shadow ray
        RTCRay shadow_ray = embree::make_ray(hit_pos, light_dir, calculate_tnear(norm_dot_light), tfar);

        RTCIntersectContext context_shadow;
        rtcInitIntersectContext(&context_shadow);
        rtcOccluded1(scene, &context_shadow, &shadow_ray);

        // We only have specualar and diffuse components if the shadow ray didn't hit anything
        if (shadow_ray.tfar > 0)
            ret += light.col * (lambert_diffusive_shader(mat, norm_dot_light) + phong_specular_shader(mat, refl_dir.dot(light_dir)));
    }

    // *************************************************************************************************************
    // REFLECTION
    // 
    // This calculates the reflection of the ray. We only do this if the depth of the recursion is less than the
    // maximum depth. We use the embree::make_ray function to make the ray, and then recursively call this function
    // again to calculate the colour of the reflected ray. We then add the colour of the reflected ray to the
    // current colour.
    // *************************************************************************************************************

    static thread_local depth_counter counter;
    auto increment = counter.increment();

    // It may be the case that the reflected ray is slightly behind the material due to the normal interpolation
    if (norm_dot_refl < 0)
        return ret;
    
    if (counter.get_depth() < max_depth)
        ret += mat.kr * trace_ray(embree::make_ray(hit_pos, refl_dir, calculate_tnear(norm_dot_refl)));

    return ret;
}

}