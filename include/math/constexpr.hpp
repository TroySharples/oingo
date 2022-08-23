#pragma once

#include <concepts>

namespace oingo::math
{

template <typename T>
requires std::unsigned<T>
constexpr auto pow(const auto& a, const T& b)
{
    decltype(a) ret = 1;
    for (size_t i = 0; i < b; i++) ret *= a;
    return ret;
}

}