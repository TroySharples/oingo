#include "geometry.hpp"

#include <Eigen/LU>

#include <stdexcept>

namespace oingo::embree
{

geometry::geometry(device& dev, RTCGeometryType type)
    : _geometry(rtcNewGeometry(dev, type))
{
    if (_geometry == nullptr)
        throw std::runtime_error("Could not create Embree geometry");
}

geometry::geometry(geometry&& other) noexcept
    : _geometry(other._geometry)
{
    other._geometry = nullptr;
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
    return *this;
}

geometry::~geometry()
{
    if (_geometry != nullptr)
        rtcReleaseGeometry(_geometry);
}

}