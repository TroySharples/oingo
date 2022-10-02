#include "render/simple_sampler.hpp"
#include "cameras/digital.hpp"
#include "objects/sphere.hpp"

#include <chrono>
#include <fstream>
#include <iostream>

using namespace oingo;

static constexpr const char* TMP_DIR = "/tmp";

static std::string make_output_name()
{
    // Our output PPM file is just the unix time for now
    return std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}

int main()
{
    scene::scene s;

    std::unique_ptr<cameras::digital> c = std::make_unique<cameras::digital>();
    s.cam = std::move(c);

    std::unique_ptr<objects::sphere> obj = std::make_unique<objects::sphere>();
    obj->translate({ 5, 0, 0 });
    s.objects.emplace_back(std::move(obj));

    film f(1920, 1080);

    render::simple_sampler r;


    const auto tmp_path = TMP_DIR + make_output_name();

    // Outputs the rendered PPM
    {
        std::ofstream os(tmp_path + ".ppm");
        r.render(s, f, os);
    }
    

    // Hacky convert any PPMs to PNGs. A much nicer way of doing this would be to use libpng
    std::system(("convert " + tmp_path + ".ppm " + tmp_path + ".png").c_str());
    std::remove((tmp_path + ".ppm").c_str());

    // Output the PPM file to stdout
    {
        std::ifstream is(tmp_path + ".png");
        std::cout << is.rdbuf();
    }
    std::remove((tmp_path + ".png").c_str());

    return EXIT_SUCCESS;
}