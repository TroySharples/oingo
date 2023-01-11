#include "integrators/simple_sampler.hpp"
#include "logging.hpp"
#include "options.hpp"
#include "ppm.hpp"

#include <chrono>
#include <fstream>
#include <iostream>

using namespace oingo;

static std::filesystem::path make_tmp_name(const std::filesystem::path& path = { })
{
    std::filesystem::path ret = path;

    // Remove any extensions if necessary
    if (ret.has_extension())
        ret.replace_extension();

    // Generate a unique filename from the current time if we weren't given one, and make the one we were given to an absolute path if we were
    if (!ret.has_filename())
        ret.replace_filename(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
    else if (!ret.has_parent_path())
        ret = std::filesystem::current_path() / ret;

    // Prepend a temporary path if we still don't have a parent directory
    if (!ret.has_parent_path())
        ret = std::filesystem::temp_directory_path() / ret;

    // Make this a hidden file by prepending "." to the file name if it isn't already hidden
    if (std::string(ret.filename())[0] != '.')
        ret.replace_filename(std::string(".") + std::string(ret.filename()));
    
    // Add the PPM extension
    ret.replace_extension(".ppm");

    return ret;
}

int main(int argc, char** argv) try
{
    // Parse options
    options opt = parse_options(argc, argv);

    // Load the test scene if necessary
    if (opt.test_scene == nullptr)
        throw std::runtime_error("We only support test scene rendering at this time");
    const scene::scene& s = *opt.test_scene;

    // Load the film
    cameras::film f(opt.horizontal_pixels, opt.vertical_pixels);

    // Render the image to a temporary PPM file
    const auto ppm_file = make_tmp_name(opt.output_file);
    {
        std::ofstream os(ppm_file);
        integrator::simple_sampler r;   
        r.render(s, f, os);
    }    

    // Converts to PNG format if necessary
    const auto formatted_file = (opt.format == options::format_t::ppm ? ppm_file : ppm_to_png(ppm_file)); 

    if (!opt.output_file.has_filename())
    {
        // Output the PPM file to stdout and delete the temporary PNG
        {
            std::ifstream is(formatted_file);
            std::cout << is.rdbuf();
        }
        std::remove(formatted_file.c_str());
    }
    else
    {
        // We try an efficient filesystem rename. If this fails due to a filesystem error (e.g. the paths are on different
        // filesystems) we try an old-fashioned copy-and-delete instead
        try 
        {
            std::filesystem::rename(formatted_file, opt.output_file);
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            std::filesystem::remove(opt.output_file);
            std::filesystem::copy(formatted_file, opt.output_file);
            if (!std::filesystem::remove(formatted_file))
                throw std::runtime_error("Could not delete " + std::string(ppm_file));
        }
    }

    return EXIT_SUCCESS;
}
catch (const std::runtime_error& e)
{
    std::cerr << colour_code::FG_RED << "Error - " << colour_code::FG_DEFAULT << e.what() << '\n';
    return EXIT_FAILURE;
}