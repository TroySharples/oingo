#pragma once

#include <optional>
#include <string>
#include <cstddef>

namespace oingo
{

struct options 
{
    enum format_t { png, ppm };
    format_t format = png;

    std::optional<std::string> output_file;

    std::size_t horizonal_pixels = 1920;
    std::size_t vertical_pixels  = 1080;
};

options parse_options(int argc, char** argv);

}