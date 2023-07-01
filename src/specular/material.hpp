#pragma once

#include "colour.hpp"

namespace oingo
{

struct material
{
    colour ke        { 0.0F };
    colour ka        { 0.0F };
    colour ks        { 0.0F };
    colour kd        { 0.0F };
    colour kt        { 0.0F };
    colour kr        { 0.0F };
    colour shininess { 0.0F };
    colour index     { 0.0F };
};

constexpr material white_matte
{
    .ke = 0.0F,
    .ka = 0.5F,
    .ks = 0.0F,
    .kd = 0.5F,
    .kt = 0.0F,
    .kr = 0.0F,
    .shininess = 0.0F,
    .index = 0.0F
};

}