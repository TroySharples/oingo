#include "plane.hpp"

namespace oingo::embree
{

plane::plane(device& dev, const Eigen::Vector3f& point, const Eigen::Vector3f& normal)
    : geometry(dev, RTC_GEOMETRY_TYPE_USER)
{
    
}

}