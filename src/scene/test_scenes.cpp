#include "test_scenes.hpp"

#include "shapes/sphere.hpp"
#include "shapes/cylinder.hpp"
#include "cameras/digital.hpp"
#include "materials/test_materials.hpp"

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
        .pos = { 5, 0, 0 },
        .trans = { 
            1, 0, 0,
            3, 5, 0,
            0, 2, 1
        },
        .mat = materials::matt_white
    });

    // Lighting
    ret.ambient_lights.push_back({ 0, 0.1, 0.1 });

    return ret;
}

static scene make_single_cylinder()
{
    scene ret;

    auto cam = std::make_unique<cameras::digital>();
    cam->fov = 1.5;
    ret.cam = std::move(cam);

    ret.objects.emplace_back(object{
        .shp = std::make_unique<shapes::cylinder>(),
        .pos = { 5, 0, 0 },
        .trans = math::rotation<floating_point_t>(0.3, 0.3, 0.3),
        .mat = materials::matt_white
    });

    ret.ambient_lights.push_back({ 0, 0.1, 0.1 });

    return ret;
}

const scene single_sphere    = make_single_sphere();
const scene multiple_spheres = make_multiple_spheres();
const scene single_cylinder  = make_single_cylinder();

}