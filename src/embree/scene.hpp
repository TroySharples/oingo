#pragma once

#include "device.hpp"

namespace oingo::embree
{

class scene
{
public:
    scene(device& dev);
    
    scene(const scene&) = delete;
    scene& operator=(const scene&) = delete;
    
    scene(scene&&) noexcept;
    scene& operator=(scene&&) noexcept;

    ~scene();

    operator RTCScene() const noexcept { return _scene; }

private:
    RTCScene _scene;
};

}