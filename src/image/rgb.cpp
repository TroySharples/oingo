#include "rgb.hpp"

#include <Eigen/Core>

namespace oingo
{

template <>
rgb to_rgb<Eigen::Vector3f>(const Eigen::Vector3f& v)
{
    return { v.x(), v.y(), v.z() };
}

}

std::ostream& operator<<(std::ostream& os, const oingo::rgb& pixel)
{
    return os << '('
              << "r - " << pixel.r << ", "
              << "g - " << pixel.g << ", "
              << "b - " << pixel.b
              << ')';
}
