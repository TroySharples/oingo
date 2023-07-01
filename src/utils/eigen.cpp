#include "eigen.hpp"

#include <Eigen/Dense>

#include <numbers>

namespace oingo::eigen
{

Eigen::Matrix3f make_rotation(float x, float y, float z)
{
    return 
        Eigen::AngleAxisf(x * std::numbers::pi_v<float> / 180.0F, Eigen::Vector3f::UnitX()).matrix().cast<float>() *
        Eigen::AngleAxisf(y * std::numbers::pi_v<float> / 180.0F, Eigen::Vector3f::UnitY()).matrix().cast<float>() *
        Eigen::AngleAxisf(z * std::numbers::pi_v<float> / 180.0F, Eigen::Vector3f::UnitZ()).matrix().cast<float>();
}

}