#pragma once

#include "rgb.hpp"

#include <span>
#include <filesystem>

namespace oingo
{

void write_to_file(const std::filesystem::path& path, std::span<const rgb> pixels, std::size_t width, std::size_t height);

}