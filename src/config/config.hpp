#pragma once

#include <cstddef>
#include <filesystem>

namespace oingo
{

struct config 
{
    config() = default;
    config(int argc, char** argv);

    std::filesystem::path input_file;
    std::filesystem::path output_file;

    std::size_t horizontal_pixels {1920};
    std::size_t vertical_pixels   {1080};

    std::size_t tile_width  {32};
    std::size_t tile_height {32};

    std::size_t depth        {1};
    std::size_t thread_count {1};

    bool help {false};
};

}