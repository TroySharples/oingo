#pragma once


#include <cstddef>
#include <filesystem>

namespace oingo
{

struct config 
{
    config() = default;
    config(int argc, char** argv);

    std::filesystem::path output_file;

    std::size_t horizontal_pixels {1920};
    std::size_t vertical_pixels   {1080};

    bool help = false;
};

}