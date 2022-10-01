#pragma once

#include "common.hpp"

#include <optional>

namespace oingo::objects
{

struct
{
    // Emissivness
    colour_t ke;
    // Ambiance
    colour_t ka;
    // Spectrum
    colour_t ks;
    // Diffusivity 
    colour_t kd;
    // Transmissivness
    colour_t kt;
    // Reflectivity (defaults to ks)
    std::optional<colour_t> kr;
    float shininess;
    float index;
};

}