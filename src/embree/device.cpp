#include "device.hpp"

#include <stdexcept>

namespace oingo::embree
{

device::device()
    : _device(rtcNewDevice(nullptr))
{
    if (_device == nullptr)
        throw std::runtime_error("Could not create Embree device");
}

device::device(device&& other) noexcept
    : _device(other._device)
{
    other._device = nullptr;
}

device& device::operator=(device&& other) noexcept
{
    if (this != &other)
    {
        if (_device != nullptr)
            rtcReleaseDevice(_device);
        _device = other._device;
        other._device = nullptr;
    }
    return *this;
}

device::~device()
{
    if (_device != nullptr)
        rtcReleaseDevice(_device);
}

}