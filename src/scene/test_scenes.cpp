#include "test_scenes.hpp"

#include "shapes/sphere.hpp"
#include "cameras/digital.hpp"

namespace oingo::scene
{

static scene make_single_sphere()
{
    scene ret;

    // Camera
    auto cam = std::make_unique<cameras::digital>();
    cam->fov = 1.5;
    ret.cam = std::move(cam);

    // Object
    ret.objects.emplace_back(object{
        .shp = std::make_unique<shapes::sphere>(),
        .pos = { 2, 0, 0 }
    });

    // Lighting
    ret.ambient_lights.push_back({ 0, 0.1, 0.2 });
    ret.directional_lights.push_back({ 
        .colour    = { 0.1, 0.2, 0.1 },
        .direction = math::normalise(spacial_t{ 1, 0.5, 0.5 })
    });
    ret.point_lights.push_back({
        .colour                     = { 1, 1, 1 },
        .position                   = { 20, -3, 3},
        .constant_attenuation_coef  = 1,
        .linear_attenuation_coef    = 0.5,
        .quadratic_attenuation_coef = 1,
    });

    return ret;
}

static scene make_multiple_spheres()
{
    // Placeholder for now
    return make_single_sphere();
}

const scene single_sphere    = make_single_sphere();
const scene multiple_spheres = make_multiple_spheres();

}