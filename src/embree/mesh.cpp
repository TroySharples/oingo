#include "mesh.hpp"

#include "Eigen/Dense"

namespace oingo::embree
{

mesh::mesh(device& dev, const aiMesh& m, const Eigen::Matrix3f& transformation, const Eigen::Vector3f& translation)
    : geometry(dev, RTC_GEOMETRY_TYPE_TRIANGLE)
{
    // Load the verticies from the mesh while applying the transformations and translations
    auto* vertex_buffer = static_cast<Eigen::Vector3f*>(rtcSetNewGeometryBuffer(_geometry, RTC_BUFFER_TYPE_VERTEX, 0, RTC_FORMAT_FLOAT3, 3 * sizeof(float), m.mNumVertices));
    for (std::size_t i = 0; i < m.mNumVertices; i++)
        vertex_buffer[i] = transformation * Eigen::Vector3f(m.mVertices[i].x, m.mVertices[i].y, m.mVertices[i].z) + translation;

    // Load the triangle indicies from the mesh
    auto* index_buffer = static_cast<std::array<unsigned int, 3>*>(rtcSetNewGeometryBuffer(_geometry, RTC_BUFFER_TYPE_INDEX, 0, RTC_FORMAT_UINT3, 3 * sizeof(unsigned int), m.mNumFaces));
    for (std::size_t i = 0; i < m.mNumFaces; i++)
        for (std::size_t j = 0; j < m.mFaces[i].mNumIndices; j++)
            index_buffer[i][j] = m.mFaces[i].mIndices[j];

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

mesh::mesh(device& dev, const aiMesh& m, const Eigen::Vector3f& translation)
    : mesh(dev, m, Eigen::Matrix3f::Identity(), translation)
{
    
}

Eigen::Vector3f mesh::get_normal(const RTCHit &hit) const
{
    Eigen::Vector3f ret;
    rtcInterpolate0(_geometry, hit.primID, hit.u, hit.v, RTC_BUFFER_TYPE_VERTEX_ATTRIBUTE, 0, ret.data(), ret.size());
    ret.normalize();
    return ret;
}

}