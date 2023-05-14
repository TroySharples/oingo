#pragma once

#include "common.hpp"

#include <optional>

namespace materials
{

struct material
{
    // Emissivness
    colour_t ke = { 0 };
    // Ambiance
    colour_t ka = { 0 };
    // Spectrum
    colour_t ks = { 0 };
    // Diffusivity 
    colour_t kd = { 0 };
    // Transmissivness
    colour_t kt = { 0 };
    // Reflectivity (defaults to ks)
    std::optional<colour_t> kr = std::nullopt;
    double shininess = 0;
    double index = 0;
};

}