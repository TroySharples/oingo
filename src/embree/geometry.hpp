#pragma once

#include "scene.hpp"

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

}