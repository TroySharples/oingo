#include "helper.hpp"

namespace oingo::embree
{

Eigen::Vector3f get_interpolated_normal(const RTCGeometry& geom, const RTCHit& hit)
{
    Eigen::Vector3f ret;
    rtcInterpolate0(geom, hit.primID, hit.u, hit.v, RTC_BUFFER_TYPE_VERTEX_ATTRIBUTE, 0, ret.data(), ret.size());
    ret.normalize();
    return ret;
}

RTCRay make_shadow_ray(const Eigen::Vector3f& hit_pos, const Eigen::Vector3f& light_dir, float distance_to_light)
{
    return RTCRay {
        .org_x = hit_pos.x(),
        .org_y = hit_pos.y(),
        .org_z = hit_pos.z(),
        .tnear = 0.1F,
        .dir_x = light_dir.x(),
        .dir_y = light_dir.y(),
        .dir_z = light_dir.z(),
        .tfar  = distance_to_light,
        .mask  = std::numeric_limits<unsigned int>::max()
    };
}

}