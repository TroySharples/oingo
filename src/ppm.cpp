#include "ppm.hpp"

namespace oingo
{
    
std::string ppm_to_png(const std::string& ppm_file)
{
    const std::string png_file = ppm_file.substr(0, ppm_file.find_last_of(".")) + ".png";
    if (std::system(("convert " + ppm_file + ' ' + png_file).c_str()) != 0)
        throw std::runtime_error("Could not convert " + ppm_file + " to " + png_file);
    
    if (std::remove(ppm_file.c_str()) != 0)
        throw std::runtime_error("Could not delete " + ppm_file);

    return png_file;
}

std::ostream& ppm_write_header(std::ostream& os, std::size_t horizontal_pixels, std::size_t vertical_pixels, std::size_t bits)
{
    return os << "P3\n" << horizontal_pixels << " " << vertical_pixels << '\n' << bits << '\n';
}

}