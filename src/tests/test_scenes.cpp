#include "test_scenes.hpp"

#include "objects/sphere.hpp"
#include "cameras/digital.hpp"

namespace oingo::test_scenes
{

static scene::scene make_spheres_scene()
{
    scene::scene ret;

    // Camera
    auto cam = std::make_unique<cameras::digital>();
    cam->fov = 1.5;
    ret.cam = std::move(cam);

    // Objects
    objects::sphere obj;
    obj.translate({ 5, -8, 0 });
    obj.scale({ 2, 2, 2 });
    obj.mat.ke = { 5, 0.8, 0 };
    obj.mat.ks = { 1, 1, 1 };
    for (std::size_t i = 0; i < 16; i++)
    {
        obj.translate({ 0, static_cast<float_t>(4*std::pow(0.7, i)), 0 });
        obj.scale({ 0.7, 0.7, 0.7 });
        ret.objects.emplace_back(obj.clone());
    }

    // Lighting
    ret.ambient_lights.push_back({ 0, 0.1, 0.2 });
    // ret.directional_lights.push_back({ 
    //     .colour    = { 0.1, 0.2, 0.1 },
    //     .direction = math::normalise(spacial_t{ 1, 0.5, 0.5 })
    // });
    // ret.point_lights.push_back({
    //     .colour                     = { 1, 1, 1 },
    //     .position                   = { 20, -3, 3},
    //     .constant_attenuation_coef  = 1,
    //     .linear_attenuation_coef    = 0.5,
    //     .quadratic_attenuation_coef = 1,
    // });

    return ret;
}

const scene::scene spheres = make_spheres_scene();

}