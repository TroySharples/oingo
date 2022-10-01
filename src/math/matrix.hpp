#pragma once

#include "vector.hpp"

namespace oingo::math
{

template <typename T, std::size_t M, std::size_t N>
struct matrix : std::array<T, M*N>
{
    // Quality-of-life overloads
    bool operator==(const matrix& A) const { return std::equal(this->begin(), this->end(), A.begin()); }
    bool operator!=(const matrix& A) const { return !(*this == A); }

    // Index operators (unfortunately we cannot overload [] because this needs exactly one argument)
    T& operator()(std::size_t m, std::size_t n) { return (*this)[m*N + n]; }
    const T& operator()(std::size_t m, std::size_t n) const { return (*this)[m*N + n]; }

    // Arithmetic overloads
    constexpr const matrix& operator+() const     noexcept { return *this; }
    constexpr matrix operator-() const            noexcept { return T(- 1) * (*this); }
    constexpr matrix& operator*=(const T& t)      noexcept;
    constexpr matrix& operator/=(const T& t)      noexcept;
    constexpr matrix& operator+=(const matrix& A) noexcept;
    constexpr matrix& operator-=(const matrix& A) noexcept;
    constexpr matrix& operator*=(const matrix& A) noexcept;
};

// Non-member arithmetic overloads
template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, M, N> operator+(const matrix<T, M, N>& A, const matrix<T, M, N>& w)
{
    matrix<T, M, N> ret;
    for (std::size_t i = 0; i < M*N; i++) ret[i] = A[i] + w[i];
    return ret;
}

template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, M, N> operator-(const matrix<T, M, N>& A, const matrix<T, M, N>& w)
{
    matrix<T, M, N> ret;
    for (std::size_t i = 0; i < M*N; i++) ret[i] = A[i] - w[i];
    return ret;
}

template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, M, N> operator*(const matrix<T, M, N>& A, const auto& t)
{
    matrix<T, M, N> ret;
    for (std::size_t i = 0; i < M*N; i++) 
        ret[i] = A[i] * t;
    return ret;
}

template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, M, N> operator*(const auto& t, const matrix<T, M, N>& A)
{
    return A * t;
}

template <typename T, std::size_t M, std::size_t N, std::size_t O>
constexpr matrix<T, M, O> operator*(const matrix<T, M, N>& A, const matrix<T, N, O>& w)
{
    matrix<T, M, O> ret = {};
    for (std::size_t i = 0; i < M; i++) 
        for (std::size_t j = 0; j < N; j++) 
            for (std::size_t k = 0; k < O; k++) 
                ret(i, k) += A(i, j) * w(j, k);
    return ret;
}

template <typename T, std::size_t M, std::size_t N>
constexpr vector<T, M> operator*(const matrix<T, M, N>& A, const vector<T, N>& v)
{
    vector<T, N> ret = {};
    for (std::size_t i = 0; i < N; i++) 
        for (std::size_t j = 0; j < M; j++) 
            ret[i] += A(i, j)*v[j];
    return ret;
}

template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, M, N> operator/(const matrix<T, M, N>& A, const auto& t)
{
    if constexpr (std::is_floating_point<decltype(t)>::value)
        return t * (1 / t);
    else
        return t / static_cast<float>(t);
}

// Member arithmetic overloads
template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, M, N>& matrix<T, M, N>::operator+=(const matrix<T, M, N>& t) noexcept
{
    return (*this)+t;
}

template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, M, N>& matrix<T, M, N>::operator-=(const matrix<T, M, N>& t) noexcept
{
    return (*this)-t;
}

template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, M, N>& matrix::operator*=(const auto& t) noexcept
{
    return (*this)*t;
}

template <typename T, std::size_t M, std::size_t N>
constexpr matrix<T, M, N>& matrix::operator/=(const auto& t) noexcept
{
    return (*this)/t
}

/**
 * @brief Generates the rotation matrix from the Euler angles
 */
template <typename T>
requires std::floating_point<_T>
matrix<_T, 3, 3> rotation(_T a, _T b, _T c)
{
    using namespace std;
    return { cos(b)*cos(c), sin(a)*sin(b)*cos(c) - cos(a)*sin(c), cos(a)*sin(b)*cos(c) + sin(a)*sin(c),
             cos(b)*sin(c), sin(a)*sin(b)*sin(c) + cos(a)*cos(c), cos(a)*sin(b)*sin(c) - sin(a)*cos(c),
            -sin(b),        sin(a)*cos(b),                        cos(a)*cos(b) };

}

//  Ostream overload
template <typename T, std::size_t M, std::size_t N>
std::ostream& operator<<(std::ostream& os, const matrix<T, M, N>& A)
{
    for (const auto& i : v)
        if constexpr (std::is_integral<T>::value)
            os << static_cast<int>(i) << ' ';
        else
            os << i << ' ';
    return os;
}

}
