#include "whitted.hpp"

#include "specular/material.hpp"
#include "embree/helper.hpp"

namespace oingo::integrator
{

static colour phong_shader(const material& mat, const Eigen::Vector3f& light_dir, const Eigen::Vector3f& norm_dir, const Eigen::Vector3f& refl_dir)
{
    const colour diffusive = mat.kd * std::max(0.0F, norm_dir.dot(light_dir));
    const colour specular  = mat.ks * std::pow(std::max(0.0F, refl_dir.dot(light_dir)), mat.shininess);

    return diffusive + specular;
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

    // Calculate the various parameters for the object we hit. These include the various geometric parameters
    // (e.g. normals, reflections, ...), and the material parameters (e.g. diffuse, specular, ...)
    const RTCGeometry geom = rtcGetGeometry(scene, rayhit.hit.geomID);

    const Eigen::Vector3f ray_dir  = Eigen::Vector3f{ rayhit.ray.dir_x, rayhit.ray.dir_y, rayhit.ray.dir_z };
    const Eigen::Vector3f cam_pos  = Eigen::Vector3f{ rayhit.ray.org_x, rayhit.ray.org_y, rayhit.ray.org_z };
    const Eigen::Vector3f hit_pos  = cam_pos + rayhit.ray.tfar * ray_dir;
    const Eigen::Vector3f norm_dir = embree::get_interpolated_normal(geom, rayhit.hit);
    const Eigen::Vector3f refl_dir = (ray_dir - 2 * ray_dir.dot(norm_dir) * norm_dir).normalized();

    const material& mat = *static_cast<material*>(rtcGetGeometryUserData(geom));
    
    // Calculate the ambient light contributions
    for (const auto& light : ambient_lights)
        ret += mat.ka * light.col;
    
    // Calculate the directional light contributions
    for (const auto& light : directional_lights)
    {
        // Make the shadow ray
        RTCRay shadow_ray = embree::make_shadow_ray(hit_pos, light.dir);

        RTCIntersectContext context_shadow;
        rtcInitIntersectContext(&context_shadow);
        rtcOccluded1(scene, &context_shadow, &shadow_ray);

        // We only have specualar and diffuse components if the shadow ray didn't hit anything
        if (shadow_ray.tfar > 0)
            ret += light.col * phong_shader(mat, light.dir, norm_dir, refl_dir) * light.col;
    }

    // Calculate the point light contributions
    for (const auto& light : point_lights)
    {
        // Calculate the light direction and distance (more efficient to calculate the norm first so we don't have to do the square-root twice)
        const float distance_to_light = (light.pos - hit_pos).norm();
        const Eigen::Vector3f light_dir = (light.pos - hit_pos) / distance_to_light;

        // Make the shadow ray
        RTCRay shadow_ray = embree::make_shadow_ray(hit_pos, light_dir, distance_to_light);

        RTCIntersectContext context_shadow;
        rtcInitIntersectContext(&context_shadow);
        rtcOccluded1(scene, &context_shadow, &shadow_ray);

        // We only have specualar and diffuse components if the shadow ray didn't hit anything
        if (shadow_ray.tfar > 0)
            ret += light.col * phong_shader(mat, light.pos - hit_pos, norm_dir, refl_dir) * light.col;
    }

    return ret;
}

}