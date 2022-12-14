#pragma once

#include <optional>
#include <string>
#include <cstddef>

namespace oingo
{

namespace scene { struct scene; }

struct options 
{
    enum format_t { png, ppm };
    format_t format = png;

    std::optional<std::string> output_file;

    std::size_t horizontal_pixels = 1920;
    std::size_t vertical_pixels  = 1080;

    const scene::scene* test_scene = nullptr;
};

options parse_options(int argc, char** argv);

}