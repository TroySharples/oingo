#include "render/simple_sampler.hpp"
#include "test_scenes.cpp"
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

    // Load the scene
    const scene::scene& s = test_scenes::spheres;

    // Load the film
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