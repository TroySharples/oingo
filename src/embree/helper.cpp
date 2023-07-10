#include "helper.hpp"

namespace oingo::embree
{

RTCRay make_ray(const Eigen::Vector3f& hit_pos, const Eigen::Vector3f& light_dir, float tnear, float tfar)
{
    return RTCRay {
        .org_x = hit_pos.x(),
        .org_y = hit_pos.y(),
        .org_z = hit_pos.z(),
        .tnear = tnear,
        .dir_x = light_dir.x(),
        .dir_y = light_dir.y(),
        .dir_z = light_dir.z(),
        .tfar  = tfar,
        .mask  = std::numeric_limits<unsigned int>::max()
    };
}

}