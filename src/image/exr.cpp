#include "exr.hpp"

#include <tinyexr.h>
#include <vector>
#include <cstring>

namespace oingo
{
    
void write_to_file(const std::filesystem::path& path, std::span<const rgb> pixels, std::size_t width, std::size_t height)
{
    // We only support three channels for now
    constexpr std::size_t num_channels = 3;

    // Checks that the image is the correct size
    if (pixels.size() != width*height)
        throw std::runtime_error(std::string("EXR image size (") + std::to_string(pixels.size()) + ") is not equal to width*height" + "(" + std::to_string(width) + "*" + std::to_string(height) + ")");

    // Make the various header fields
    std::array<int, num_channels> pixel_types, requested_pixel_types;
    std::array<EXRChannelInfo, num_channels> channels;
    for (std::size_t i = 0; i < num_channels; i++)
    {
        pixel_types[i]           = TINYEXR_PIXELTYPE_FLOAT;
        requested_pixel_types[i] = TINYEXR_PIXELTYPE_HALF;
        ::strncpy(static_cast<char*>(channels[i].name), "\0", 256);
    }
    channels[0].name[0] = 'B', channels[1].name[0] = 'G', channels[2].name[0] = 'R';

    // Creates the EXR header
    EXRHeader header;
    InitEXRHeader(&header);
    header.num_channels          = static_cast<int>(num_channels);
    header.pixel_types           = pixel_types.data();
    header.requested_pixel_types = requested_pixel_types.data();
    header.channels              = channels.data();

    // Separate out the RGB channels and stick them in an array in BGR order
    std::vector<float> r(width*height), g(width*height), b(width*height);
    for (std::size_t i = 0; i < width*height; i++)
    {
        r[i] = pixels[i].r;
        g[i] = pixels[i].g;
        b[i] = pixels[i].b;
    }
    std::array<float*, 3> images { b.data(), g.data(), r.data() };

    // Creates the EXR image
    EXRImage image;
    InitEXRImage(&image);
    image.num_channels = num_channels;
    image.images       = reinterpret_cast<unsigned char**>(images.data());
    image.width        = static_cast<int>(width);
    image.height       = static_cast<int>(height);

    // Write the EXR image to the file and throw an error if it fails
    if (int ret = SaveEXRImageToFile(&image, &header, path.c_str(), nullptr); ret != TINYEXR_SUCCESS)
        throw std::runtime_error("Failed to write EXR image to file with error code " + std::to_string(ret));
}

}