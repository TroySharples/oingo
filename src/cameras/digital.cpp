#include "digital.hpp"

namespace oingo::cameras
{

ray_t digital::generate_ray(const film& f, std::size_t hori, std::size_t vert)
{
    if (hori >= f.horizontal_pixels || vert >= f.vertical_pixels)
        throw std::runtime_error("Invalid pixel positon");

    const float_t aspect_ratio = static_cast<float>(f.horizontal_pixels)/f.vertical_pixels;
    const spacial_t view = aspect_ratio * (0.5 - static_cast<float_t>(hori + 1)/f.horizontal_pixels) * _leftdir
                                        + (0.5 - static_cast<float_t>(vert + 1)/f.vertical_pixels)   * _updir;
    return { .origin = position, .direction = _viewdir + fov * view };
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