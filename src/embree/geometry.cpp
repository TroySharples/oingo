#include "geometry.hpp"

#include <stdexcept>
#include <Eigen/LU>

namespace oingo::embree
{

geometry::geometry(device& dev, RTCGeometryType type)
    : _geometry(rtcNewGeometry(static_cast<RTCDevice>(dev), type))
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

mesh::mesh(device& dev, const aiMesh& m, const Eigen::Matrix3f& transformation, const Eigen::Vector3f& translation)
    : geometry(dev, RTC_GEOMETRY_TYPE_TRIANGLE)
{
    // Load the verticies from the mesh while applying the transformations and translations
    auto* vertex_buffer = static_cast<Eigen::Vector3f*>(rtcSetNewGeometryBuffer(_geometry, RTC_BUFFER_TYPE_VERTEX, 0, RTC_FORMAT_FLOAT3, 3 * sizeof(float), m.mNumVertices));
    for (std::size_t i = 0; i < m.mNumVertices; i++)
        vertex_buffer[i] = transformation * Eigen::Vector3f(m.mVertices[i].x, m.mVertices[i].y, m.mVertices[i].z) + translation;

    // Load the triangle indicies from the mesh
    auto* index_buffer = static_cast<Eigen::Vector3i*>(rtcSetNewGeometryBuffer(_geometry, RTC_BUFFER_TYPE_INDEX, 0, RTC_FORMAT_UINT3, 3 * sizeof(unsigned int), m.mNumFaces));
    for (std::size_t i = 0; i < m.mNumFaces; i++)
        index_buffer[i] = Eigen::Vector3i(m.mFaces[i].mIndices[0], m.mFaces[i].mIndices[1], m.mFaces[i].mIndices[2]);

    // We can do normal smoothing by loading in the vertex normals from the mesh. We can save this as a RTC_BUFFER_TYPE_VERTEX_ATTRIBUTE, which we can then interpolate over
    // when rendering. We have to remember to apply the right transformations to the normals (it isn't the same as the vertex transformations!)
    const Eigen::Matrix3f& normal_transformation = transformation.inverse().transpose();
    
    rtcSetGeometryVertexAttributeCount(_geometry, 1);
    auto* normal_buffer = static_cast<Eigen::Vector3f*>(rtcSetNewGeometryBuffer(_geometry, RTC_BUFFER_TYPE_VERTEX_ATTRIBUTE, 0, RTC_FORMAT_FLOAT3, 3 * sizeof(float), m.mNumVertices));
    for (std::size_t i = 0; i < m.mNumVertices; i++)
        normal_buffer[i] = normal_transformation * Eigen::Vector3f(m.mNormals[i].x, m.mNormals[i].y, m.mNormals[i].z);

    // Commit the geometry - there's more we can do here (e.g. load texture coordinates, setup BVH), but this is enough for now
    rtcCommitGeometry(_geometry);
}

}