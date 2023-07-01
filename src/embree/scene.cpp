#include "scene.hpp"

#include <stdexcept>

namespace oingo::embree
{

scene::scene(device& dev)
    : _scene(rtcNewScene(dev))
{
    if (_scene == nullptr)
        throw std::runtime_error("Could not create Embree scene");
}

scene::scene(scene&& other) noexcept
    : _scene(other._scene)
{
    other._scene = nullptr;
}

scene& scene::operator=(scene&& other) noexcept
{
    if (this != &other)
    {
        if (_scene != nullptr)
            rtcReleaseScene(_scene);
        _scene = other._scene;
        other._scene = nullptr;
    }
    return *this;
}

scene::~scene()
{
    if (_scene != nullptr)
        rtcReleaseScene(_scene);
}

}