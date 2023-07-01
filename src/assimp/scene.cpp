#include "scene.hpp"

#include <assimp/postprocess.h>

namespace oingo::assimp
{

scene::scene(const std::filesystem::path& path)
{
    // Set importer properties and load the scene in high quality
    _importer.SetPropertyFloat(AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, 80.0F);
    _scene = _importer.ReadFile(path.c_str(), aiProcessPreset_TargetRealtime_Quality);

    // Make sure we were able to load the scene properly
    if (_scene == nullptr)
        throw std::runtime_error(std::string("Unable to load scene from file") + path.string());
    if ((_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) != 0)
        throw std::runtime_error(std::string("Scene is incomplete") + path.string());
    if (_scene->mRootNode == nullptr)
        throw std::runtime_error(std::string("Scene has no root node") + path.string());

    // Make sure the scene has at least one mesh
    if (_scene->mNumMeshes == 0)
        throw std::runtime_error(std::string("Scene has no meshes") + path.string());
}


}