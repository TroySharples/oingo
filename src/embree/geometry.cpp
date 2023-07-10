#include "geometry.hpp"

#include <Eigen/LU>

#include <embree3/rtcore_geometry.h>
#include <stdexcept>

namespace oingo::embree
{

geometry::geometry(device& dev, RTCGeometryType type)
    : _geometry(rtcNewGeometry(dev, type))
{
    if (_geometry == nullptr)
        throw std::runtime_error("Could not create Embree geometry");
    rtcSetGeometryUserData(_geometry, this);
}

geometry::geometry(geometry&& other) noexcept
    : _geometry(other._geometry)
{
    other._geometry = nullptr;
    rtcSetGeometryUserData(_geometry, this);
}

geometry& geometry::operator=(geometry&& other) noexcept
{
    if (this != &other)
    {
        if (_geometry != nullptr)
            rtcReleaseGeometry(_geometry);
        _geometry = other._geometry;
        other._geometry = nullptr;
    }
    rtcSetGeometryUserData(_geometry, this);
    return *this;
}

geometry::~geometry()
{
    if (_geometry != nullptr)
        rtcReleaseGeometry(_geometry);
}

Eigen::Vector3f geometry::get_normal(const RTCHit& hit) const
{
    return Eigen::Vector3f({hit.Ng_x, hit.Ng_y, hit.Ng_z}).normalized();
}

}