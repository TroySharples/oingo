#include "plane.hpp"

#include <embree3/rtcore_geometry.h>
#include <embree3/rtcore_ray.h>
#include <Eigen/Dense>

namespace oingo::embree
{

plane::plane(device& dev, const Eigen::Vector3f& norm, const Eigen::Vector3f& p, float size)
    : geometry(dev, RTC_GEOMETRY_TYPE_QUAD)
{
    // Find two directions orthogonal to the normal
    const Eigen::Vector3f u = (norm.x() != 0 || norm.y() != 0 ? Eigen::Vector3f(-norm.y(), norm.x(), 0) : Eigen::Vector3f(0, -norm.z(), norm.y())).normalized();
    const Eigen::Vector3f v = norm.cross(u).normalized();

    // Load the four corners of the plane in the mesh vertex buffer
    auto* vertex_buffer = static_cast<Eigen::Vector3f*>(rtcSetNewGeometryBuffer(_geometry, RTC_BUFFER_TYPE_VERTEX, 0, RTC_FORMAT_FLOAT3, 3 * sizeof(float), 4));
    vertex_buffer[0] = p + ( -u - v) * size / 2;
    vertex_buffer[1] = p + (  u - v) * size / 2;
    vertex_buffer[2] = p + (  u + v) * size / 2;
    vertex_buffer[3] = p + ( -u + v) * size / 2;

    // Load the one index buffer
    auto* index_buffer = static_cast<std::array<unsigned int, 4>*>(rtcSetNewGeometryBuffer(_geometry, RTC_BUFFER_TYPE_INDEX, 0, RTC_FORMAT_UINT4, 4 * sizeof(unsigned int), 1));
    index_buffer[0] = { 0, 1, 2, 3 };

    // Do the trivial normal smoothing
    rtcSetGeometryVertexAttributeCount(_geometry, 1);
    auto* normal_buffer = static_cast<Eigen::Vector3f*>(rtcSetNewGeometryBuffer(_geometry, RTC_BUFFER_TYPE_VERTEX_ATTRIBUTE, 0, RTC_FORMAT_FLOAT3, 3 * sizeof(float), 4));
    for (std::size_t i = 0; i < 4; i++)
        normal_buffer[i] = norm;

    // Commit the geometry 
    rtcCommitGeometry(_geometry);
}

}