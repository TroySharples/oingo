#include "integrators/whitted.hpp"
#include "utils/logging.hpp"
#include "assimp/scene.hpp"
#include "embree/mesh.hpp"
#include "embree/plane.hpp"
#include "specular/material.hpp"
#include "images/pinhole.hpp"
#include "images/exr.hpp"
#include "utils/eigen.hpp"
#include "config/config.hpp"

#include <fstream>
#include <iostream>

using namespace oingo;

int main(int argc, char** argv) try
{
    // Parse arguments
    config cfg(argc, argv);

    // Load an Embree device and scene
    embree::device embree_device;
    embree::scene embree_scene(embree_device);

    // Make a scene to be rendered
    integrator::whitted integrator;
    integrator.depth = cfg.depth;

    // Add the various geometries to the scene
    {
        // Load the object mesh
        assimp::scene assimp_scene(cfg.input_file);

        // The two meshes are the same, but with different transformations  
        integrator.geometries.emplace_back(std::make_unique<embree::mesh>(embree_device, *static_cast<const aiScene*>(assimp_scene)->mMeshes[0], eigen::make_rotation(0, 120, 0), Eigen::Vector3f{14, -1,  7}));
        integrator.geometries.emplace_back(std::make_unique<embree::mesh>(embree_device, *static_cast<const aiScene*>(assimp_scene)->mMeshes[0], eigen::make_rotation(0,  90, 0), Eigen::Vector3f{14,  1, -3}));

        // The planes to visualise the lights
        integrator.geometries.emplace_back(std::make_unique<embree::plane>(embree_device, Eigen::Vector3f{ 0,  1,  0}, Eigen::Vector3f{ 0, -6,  0 }));
        integrator.geometries.emplace_back(std::make_unique<embree::plane>(embree_device, Eigen::Vector3f{-1,  0,  0}, Eigen::Vector3f{20,  0,  0 }));
        integrator.geometries.emplace_back(std::make_unique<embree::plane>(embree_device, Eigen::Vector3f{ 0,  0,  1}, Eigen::Vector3f{0 ,  0, -12}));

        // Attach the geometries to the scene and give them a material
        for (auto& i : integrator.geometries)
        {
            rtcAttachGeometry(embree_scene, *i);
            i->mat = materials::white_gloss;
        }
    }
    rtcCommitScene(embree_scene);

    // Add the lights and camera to the scene
    {
        integrator.cam = std::make_unique<camera::pinhole>(
            Eigen::Vector3f{0, 0, 0}, Eigen::Vector3f{1, 0, 0}, Eigen::Vector3f{0, 1, 0}, 1
        );

        integrator.ambient_lights.emplace_back(0.1);

        integrator.directional_lights.emplace_back(lights::directional{
            .col = 0.1, .dir = Eigen::Vector3f{-1, 0, 1}.normalized()
        });
        
        integrator.point_lights.emplace_back(lights::point{
            .col = 0.2, .pos = Eigen::Vector3f{15, 5, 0}
        });

        integrator.scene = embree_scene;
    }

    // Make a film with a single tile
    film f(cfg.horizontal_pixels, cfg.vertical_pixels);
    film::tile& t = static_cast<std::span<film::tile>>(f)[0];

    // Render the scene
    integrator.render(t);

    // Write it to file
    exr::write_to_file(cfg.output_file, f);

    return EXIT_SUCCESS;
}
catch (const std::runtime_error& e)
{
    std::cerr << colour_code::FG_RED << "Error - " << colour_code::FG_DEFAULT << e.what() << '\n';
    return EXIT_FAILURE;
}