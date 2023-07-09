#include "plane.hpp"
#include <embree3/rtcore_geometry.h>
#include <embree3/rtcore_ray.h>

namespace oingo::embree
{

static void intersect(const struct RTCIntersectFunctionNArguments* args) noexcept
{
    // We are only able to handle single rays at the moment
    if (args->N != 1)
        std::terminate();

    auto& rayhit = reinterpret_cast<RTCRayHit&>(*args->rayhit);
    if (*args->valid == 0)
        return;

    // Don't do anything if the tfar parameter is invalid
    if (rayhit.ray.tfar < 0)
        return;

    // Get the plane geometry object that was registered with the user data
    const auto& p = *static_cast<const oingo::embree::plane*>(args->geometryUserPtr);

    // Get the Eigen vectors for the ray origin and direction
    const Eigen::Vector3f org(rayhit.ray.org_x,
                                rayhit.ray.org_y,
                                rayhit.ray.org_z);
    const Eigen::Vector3f dir(rayhit.ray.dir_x,
                                rayhit.ray.dir_y,
                                rayhit.ray.dir_z);   

    const float norm_dot_dir = p.norm.dot(dir);

    // Return if the ray is parallel to the plane
    if (norm_dot_dir == 0)
        return;

    const float t = (p.l - p.norm.dot(org)) / norm_dot_dir;

    // Return if the ray is behind the plane or if its further away than tfar
    if (t < 0 || t > rayhit.ray.tfar)
        return;

    // We have a hit! Fill out the rayhit structure
    rayhit.ray.tfar = t;

    // We have to invert the returned normal if the ray is coming from behind
    rayhit.hit.Ng_x = (norm_dot_dir < 0 ? p.norm.x() : -p.norm.x());
    rayhit.hit.Ng_y = (norm_dot_dir < 0 ? p.norm.y() : -p.norm.y());
    rayhit.hit.Ng_z = (norm_dot_dir < 0 ? p.norm.z() : -p.norm.z());
}

static void bounds(const struct RTCBoundsFunctionArguments* args) noexcept
{
    // For now we just we just set the bounds to infinity in all directions - this
    // will always be the case for a plane that is not axis aligned
    args->bounds_o->lower_x = -std::numeric_limits<float>::min();
    args->bounds_o->lower_y = -std::numeric_limits<float>::min();
    args->bounds_o->lower_z = -std::numeric_limits<float>::min();
    args->bounds_o->upper_x =  std::numeric_limits<float>::max();
    args->bounds_o->upper_y =  std::numeric_limits<float>::max();
    args->bounds_o->upper_z =  std::numeric_limits<float>::max();
}

static void occluded(const struct RTCOccludedFunctionNArguments* args) noexcept
{
    // We are only able to handle single rays at the moment
    if (args->N != 1)
        std::terminate();

    auto& ray = reinterpret_cast<RTCRay&>(*args->ray);
    if (*args->valid == 0)
        return;

    // Don't do anything if the tfar parameter is invalid
    if (ray.tfar < 0)
        return;

    // Get the plane geometry object that was registered with the user data
    const auto& p = *static_cast<const oingo::embree::plane*>(args->geometryUserPtr);

    // Get the Eigen vectors for the ray origin and direction
    const Eigen::Vector3f org(ray.org_x,
                                ray.org_y,
                                ray.org_z);
    const Eigen::Vector3f dir(ray.dir_x,
                                ray.dir_y,
                                ray.dir_z);   

    const float norm_dot_dir = p.norm.dot(dir);

    // Return if the ray is parallel to the plane
    if (norm_dot_dir == 0)
        return;

    const float t = (p.l - p.norm.dot(org)) / norm_dot_dir;

    // Return if the ray is behind the plane or if its further away than tfar
    if (t < 0 || t > ray.tfar)
        return;

    // We have a hit! Fill out the rayhit structure
    ray.tfar = t;
}

plane::plane(device& dev, Eigen::Vector3f norm, float l)
    : geometry(dev, RTC_GEOMETRY_TYPE_USER), norm(std::move(norm)), l(l)
{
    rtcSetGeometryUserPrimitiveCount(_geometry, 1);
    rtcSetGeometryIntersectFunction(_geometry, &intersect);
    rtcSetGeometryBoundsFunction(_geometry, &bounds, nullptr);
    rtcSetGeometryOccludedFunction(_geometry, &occluded);
    rtcCommitGeometry(_geometry);
}

}