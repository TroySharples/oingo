#pragma once

#include <iostream>

namespace oingo
{

struct rgb
{
    float r;
    float g;
    float b;
};

constexpr rgb RED   { 1.0F, 0.0F, 0.0F };
constexpr rgb GREEN { 0.0F, 1.0F, 0.0F };
constexpr rgb BLUE  { 0.0F, 0.0F, 1.0F };

template <typename T>
rgb to_rgb(const T& v);

}

std::ostream& operator<<(std::ostream& os, const oingo::rgb& v);