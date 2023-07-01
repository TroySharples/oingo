#include "integrators/whitted.hpp"
#include "utils/logging.hpp"
#include "assimp/scene.hpp"
#include "embree/geometry.hpp"
#include "specular/material.hpp"
#include "images/pinhole.hpp"
#include "images/exr.hpp"
#include "utils/eigen.hpp"

#include <fstream>
#include <iostream>

using namespace oingo;

int main(int argc, char** argv) try
{
    // Parse arguments
    if (argc != 3)
        throw std::runtime_error("Usage: " + std::string(argv[0]) + " <input OBJ file> <output EXR file>");
    std::filesystem::path obj_path = argv[1];
    std::filesystem::path exr_path = argv[2];

    // Load an Embree device and scene
    embree::device embree_device;
    embree::scene embree_scene(embree_device);

    // Create a white matte material to attach to our geometries
    material mat = white_gloss;

    // Add the mesh to the scene twice
    {
        // Load the object mesh
        assimp::scene assimp_scene(obj_path);

        // Mesh 0
        embree::mesh geom0(embree_device, *static_cast<const aiScene*>(assimp_scene)->mMeshes[0], eigen::make_rotation(0, 120, 0), Eigen::Vector3f{14, -1, 5});
        rtcSetGeometryUserData(geom0, static_cast<void*>(&mat));
        rtcAttachGeometry(embree_scene, geom0);
        
        // Mesh 1
        embree::mesh geom1(embree_device, *static_cast<const aiScene*>(assimp_scene)->mMeshes[0], eigen::make_rotation(0, 90, 0), Eigen::Vector3f{14, 1, -5});
        rtcSetGeometryUserData(geom1, static_cast<void*>(&mat));
        rtcAttachGeometry(embree_scene, geom1);
    }
    rtcCommitScene(embree_scene);

    // Make a scene to be rendered
    integrator::whitted integrator;
    {
        integrator.cam = std::make_unique<camera::pinhole>(
            Eigen::Vector3f{0, 0, 0}, Eigen::Vector3f{1, 0, 0}, Eigen::Vector3f{0, 1, 0}, 1
        );

        integrator.ambient_lights.emplace_back(0.1);

        integrator.directional_lights.emplace_back(lights::directional{
            .col = 0.1, .dir = Eigen::Vector3f{-10, 0, -1}.normalized()
        });
        integrator.directional_lights.emplace_back(lights::directional{
            .col = 0.3, .dir = Eigen::Vector3f{1, 0, 5}.normalized()
        });
        
        integrator.point_lights.emplace_back(lights::point{
            .col = 0.2, .pos = Eigen::Vector3f{15, 5, 0}
        });

        integrator.scene = embree_scene;
    }

    // Make a 1920x1080 film with a single tile
    film f(1920, 1080);
    film::tile& t = static_cast<std::span<film::tile>>(f)[0];

    // Render the scene
    integrator.render(t);

    // Write it to file
    exr::write_to_file(exr_path, f);

    return EXIT_SUCCESS;
}
catch (const std::runtime_error& e)
{
    std::cerr << colour_code::FG_RED << "Error - " << colour_code::FG_DEFAULT << e.what() << '\n';
    return EXIT_FAILURE;
}