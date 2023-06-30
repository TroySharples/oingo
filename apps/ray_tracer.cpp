#include "integrators/whitted.hpp"
#include "utils/logging.hpp"
#include "assimp/scene.hpp"
#include "embree/geometry.hpp"
#include "images/pinhole.hpp"

#include <fstream>
#include <iostream>

using namespace oingo;

int main(int argc, char** argv) try
{
    // Parse object file
    if (argc != 1)
    {
        std::cerr << "Usage: " << argv[0] << " <object file>\n";
        return EXIT_FAILURE;
    }

    // Load the object mesh
    std::filesystem::path obj_path = "argv[1]";
    assimp::scene assimp_scene(obj_path);

    // Load an Embree device and scene
    embree::device embree_device;
    embree::scene embree_scene(embree_device);

    // Add the mesh to the scene
    {
        embree::mesh geom(embree_device, *static_cast<const aiScene*>(assimp_scene)->mMeshes[0]);
        rtcAttachGeometry(static_cast<RTCScene>(embree_scene), static_cast<RTCGeometry>(geom));
    }

    // Make a scene to be rendered
    integrator::whitted integrator;
    {
        integrator.cam = std::make_unique<camera::pinhole>(
            Eigen::Vector3f{0, 0, 0}, Eigen::Vector3f{1, 0, 0}, Eigen::Vector3f{0, 1, 0}, 1
        );

        integrator.ambient_lights.emplace_back(0.5);

        integrator.scene = &embree_scene;
    }

    // Make a 1920x1080 film with a single tile
    film f(1920, 1080);
    film::tile& t = static_cast<std::span<film::tile>>(f)[0];

    // Render the scene
    integrator.render(t);

    return EXIT_SUCCESS;
}
catch (const std::runtime_error& e)
{
    std::cerr << colour_code::FG_RED << "Error - " << colour_code::FG_DEFAULT << e.what() << '\n';
    return EXIT_FAILURE;
}