#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <filesystem>

namespace oingo::assimp
{

class scene
{
public:
    scene(const std::filesystem::path& path);

    explicit operator const aiScene*() const noexcept { return _scene; }

private:
    Assimp::Importer _importer;
    const aiScene* _scene = nullptr;
};

}