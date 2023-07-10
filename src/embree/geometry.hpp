#pragma once

#include "scene.hpp"

#include "specular/material.hpp"

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

    material mat;

    // Override this to modify the normal of the hit (e.g. for interpolation)
    virtual Eigen::Vector3f get_normal(const RTCHit& hit) const;

protected:
    RTCGeometry _geometry;
};

}