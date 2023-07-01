#pragma once

#include <embree3/rtcore.h>
#include "Eigen/Core"

namespace oingo::embree
{

Eigen::Vector3f get_interpolated_normal(const RTCGeometry& geom, const RTCHit& hit);

RTCRay make_shadow_ray(const Eigen::Vector3f& hit_pos, const Eigen::Vector3f& light_dir, float distance_to_light = std::numeric_limits<float>::infinity());

}