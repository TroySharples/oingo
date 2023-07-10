#pragma once

#include "colour.hpp"

namespace oingo
{

struct material
{
    colour ke       { colours::black };
    colour ka       { colours::black };
    colour ks       { colours::black };
    colour kd       { colours::black };
    colour kt       { colours::black };
    colour kr       { colours::black };
    float shininess { 0.0F };
    float index     { 0.0F };
};

namespace materials 
{

constexpr material white_matte
{
    .ka = 0.5F * colours::white,
    .kd = 0.5F * colours::white
};

constexpr material white_gloss
{
    .ka        = 0.2F * colours::white,
    .ks        = 0.9F * colours::white,
    .kd        = 0.2F * colours::white,
    .kr        = 0.9F * colours::white,
    .shininess = 1.0F
};

}

}