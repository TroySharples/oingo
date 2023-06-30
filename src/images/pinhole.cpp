#include "pinhole.hpp"

#include <limits>

namespace oingo
{

pinhole::pinhole(Eigen::Vector3f pos, Eigen::Vector3f lookdir, Eigen::Vector3f updir, float fl)
    : pos(std::move(pos)), lookdir(std::move(lookdir)), updir(std::move(updir)), rightdir(updir.cross(lookdir)), fl(fl)
{
    
}

RTCRay pinhole::generate_ray(const film::tile& t, std::size_t x, std::size_t y) const
{   
    RTCRay ret;

    // Cast the camera position to the Embree format
    ret.org_x = pos.x();
    ret.org_y = pos.y();
    ret.org_z = pos.z();

    // Calculate the ray direction and cast it to the Embree format
    Eigen::Vector3f dir = lookdir  * fl
                        + rightdir * (0.5F - static_cast<float>(t.x_min + x) / static_cast<float>(t.get_film_width())) * t.get_film_aspect_ratio()
                        + updir    * (0.5F - static_cast<float>(t.y_min + y) / static_cast<float>(t.get_film_height()));
    dir.normalize();
    
    ret.dir_x = dir.x();
    ret.dir_y = dir.y();
    ret.dir_z = dir.z();

    // Set the Embree clipping parameters - these are always constant for now
    ret.tnear = std::numeric_limits<float>::epsilon();
    ret.tfar  = std::numeric_limits<float>::infinity();

    // Set the Embree layer mask to -1 (i.e. no mask is applied)
    ret.mask = -1;

    return ret;
}

}