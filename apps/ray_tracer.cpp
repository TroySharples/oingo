#include "render/simple_sampler.hpp"
#include "cameras/digital.hpp"
#include "objects/sphere.hpp"
#include "options.hpp"
#include "ppm.hpp"

#include <chrono>
#include <fstream>
#include <filesystem>
#include <iostream>

using namespace oingo;

static std::string make_tmp_name()
{
    // Our temporary PPM file is just the unix time for now
    static constexpr const char* TMP_PREFIX = "/tmp/.";
    return TMP_PREFIX + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

int main(int argc, char** argv)
{
    // Parse options
    options opt = parse_options(argc, argv);

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
    s.point_lights.push_back({
        .colour                     = { 1, 1, 1 },
        .position                   = { 3, -1, 0},
        .constant_attenuation_coef  = 1,
        .linear_attenuation_coef    = 1,
        .quadratic_attenuation_coef = 0,
    });

    // Film
    film f(opt.horizonal_pixels, opt.vertical_pixels);

    // Render the image in PPM format
    const auto ppm_file = make_tmp_name() + ".ppm";
    {
        std::ofstream os(ppm_file);
        render::simple_sampler r;   
        r.render(s, f, os);
    }    

    // Converts to PNG format if necessaary
    const auto formatted_file = opt.format == options::format_t::ppm ? ppm_file : ppm_to_png(ppm_file); 

    if (opt.output_file)
    {
        if (std::system(("mv " + formatted_file + ' ' + opt.output_file.value()).c_str()) != 0)
            throw std::runtime_error("Unable to move file");
    }
    else
    {
        // Output the PPM file to stdout and delete the temporary PNG
        std::ifstream is(formatted_file);
        std::cout << is.rdbuf();
        std::remove(formatted_file.c_str());
    }

    return EXIT_SUCCESS;
}