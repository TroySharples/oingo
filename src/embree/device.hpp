#pragma once

#include <embree3/rtcore.h>

namespace oingo::embree
{

class device
{
public:
    device();

    device(const device&) = delete;
    device& operator=(const device&) = delete;

    device(device&&) noexcept;
    device& operator=(device&&) noexcept;

    ~device();

    operator RTCDevice() const noexcept { return _device; }

private:
    RTCDevice _device;
};

}