#include "pinhole.hpp"

#include "embree/helper.hpp"

#include <Eigen/Dense>

#include <limits>

namespace oingo::camera
{

pinhole::pinhole(Eigen::Vector3f pos_, Eigen::Vector3f lookdir_, Eigen::Vector3f updir_, float fl_)
    : pos(std::move(pos_)), lookdir(std::move(lookdir_)), updir(std::move(updir_)), rightdir(updir.cross(lookdir)), fl(fl_)
{
    
}

RTCRay pinhole::generate_ray(const film::tile& t, std::size_t x, std::size_t y) const
{   
    // Calculate the ray direction with the aspect ratio of the parent film
    Eigen::Vector3f dir = lookdir  * fl
                        + rightdir * (0.5F - static_cast<float>(t.x_min + x) / static_cast<float>(t.get_film_width())) * t.get_film_aspect_ratio()
                        + updir    * (0.5F - static_cast<float>(t.y_min + y) / static_cast<float>(t.get_film_height()));
    dir.normalize();

    return oingo::embree::make_ray(pos, dir);
}

}