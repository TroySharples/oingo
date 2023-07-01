#pragma once

#include "scene.hpp"

#include "assimp/mesh.h"
#include "Eigen/Core"

namespace oingo::embree
{

class geometry
{
public:
    geometry(device& dev, RTCGeometryType type);

    geometry(const geometry&) = delete;
    geometry& operator=(const geometry&) = delete;

    geometry(geometry&&) noexcept;
    geometry& operator=(geometry&&) noexcept;

    virtual ~geometry();

    operator RTCGeometry() const noexcept { return _geometry; }

protected:
    RTCGeometry _geometry;
};

class mesh : public geometry
{
public:
    mesh(device& dev, const aiMesh& m, const Eigen::Matrix3f& transformation = Eigen::Matrix3f::Identity(), const Eigen::Vector3f& translation = { 0, 0 ,0 });
    mesh(device& dev, const aiMesh& m, const Eigen::Vector3f& translation = { 0, 0 ,0 });
};

class sphere : public geometry
{
public:
    sphere(device& dev, const Eigen::Vector3f& center, float radius);
};

}