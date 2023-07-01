#pragma once

#include "film.hpp"

#include <span>
#include <filesystem>

namespace oingo::exr
{

void write_to_file(const std::filesystem::path& path, const film& f);

}