#include "digital.hpp"

namespace oingo::cameras
{

ray_t digital::generate_ray(const film& f, std::size_t hori, std::size_t vert)
{
    if (hori >= f.horizontal_pixels || vert >= f.vertical_pixels)
        throw std::runtime_error("Invalid pixel positon");

    const spacial_t aspect = (1 - (hori + 1)/static_cast<float_t>(f.horizontal_pixels)) * _leftdir
                           + (1 - (vert + 1)/static_cast<float_t>(f.vertical_pixels))   * _updir;
    return { .origin = position, .direction = _viewdir + fov * aspect };
}

void digital::set_viewdir(const spacial_t& viewdir)
{
    _viewdir = math::normalise(viewdir);

}

void digital::set_updir(const spacial_t& updir)
{
    _updir = math::normalise(updir);
}

void digital::set_leftdir()
{
    if (math::dot_product(_viewdir, _updir) > epsilon)
        throw std::runtime_error("Invalid camera orientation - viewdir and updir are not orthogonal");

    _leftdir = math::cross_product(_viewdir, _updir);
}

}