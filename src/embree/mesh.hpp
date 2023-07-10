#pragma once

#include "geometry.hpp"

#include "assimp/mesh.h"

namespace oingo::embree
{

class mesh : public geometry
{
public:
    mesh(device& dev, const aiMesh& m, const Eigen::Matrix3f& transformation = Eigen::Matrix3f::Identity(), const Eigen::Vector3f& translation = { 0, 0 ,0 });
    mesh(device& dev, const aiMesh& m, const Eigen::Vector3f& translation = { 0, 0 ,0 });

    Eigen::Vector3f get_normal(const RTCHit& hit) const override;
};

}