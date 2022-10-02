#include "render/simple_sampler.hpp"
#include "cameras/digital.hpp"
#include "objects/sphere.hpp"

#include <chrono>
#include <fstream>
#include <iostream>

using namespace oingo;

static constexpr const char* TMP_PREFIX = "/tmp/.";

static std::string make_output_name()
{
    // Our output PPM file is just the unix time for now
    return std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

int main()
{
    scene::scene s;

    // Camera
    auto cam = std::make_unique<cameras::digital>();
    cam->fov = 2;
    s.cam = std::move(cam);

    // Objects
    auto obj = std::make_unique<objects::sphere>();
    obj->translate({ 5, 0, 0 });
    obj->mat.ke = { 0.8, 0.8, 0 };
    s.objects.emplace_back(std::move(obj));

    // Lighting
    s.ambient_lights.push_back({ 0, 0.1, 0.2 });
    s.directional_lights.push_back({ 
        .colour    = { 0.3, 0.6, 0.1 },
        .direction = math::normalise(spacial_t{ 1, 0.5, 0.5 })
    });

    // Film
    film f(1920, 1080);

    // We initially write the file to PPM format in a temporary directory
    const auto tmp_name = TMP_PREFIX + make_output_name();

    // Render the image in PPM format
    {
        std::ofstream os(tmp_name + ".ppm");
        render::simple_sampler r;   
        r.render(s, f, os);
    }    

    // Hacky convert any PPMs to PNGs. A much nicer way of doing this would be to use libpng
    if (std::system(("convert " + tmp_name + ".ppm " + tmp_name + ".png").c_str()) != 0)
        throw std::runtime_error("Could not convert file to PPM");
    std::remove((tmp_name + ".ppm").c_str());

    // Output the PPM file to stdout and delete the temporary PNG
    {
        std::ifstream is(tmp_name + ".png");
        std::cout << is.rdbuf();
    }
    std::remove((tmp_name + ".png").c_str());

    return EXIT_SUCCESS;
}