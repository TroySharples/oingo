#include "config.hpp"


#include <cstring>
#include <stdexcept>

#include <unistd.h>

namespace oingo
{

config::config(int argc, char** argv)
{
    for (int c; (c = getopt(argc, argv, "hr:d:i:o:s:")) != -1; )
    {
        switch (c)
        {   
            // Help
            case 'h':
            {
                help = true;
                break;
            }
            // Resolution
            case 'r':
            {
                const std::string resolution = std::string(optarg);
                const std::size_t xpos = resolution.find('x');
                horizontal_pixels = std::stoi(resolution.substr(0, xpos));
                vertical_pixels  = std::stoi(resolution.substr(xpos + 1, resolution.length()));
                break;
            }
            // Depth
            case 'd':
            {
                depth = std::stoi(optarg);
                break;
            }
            // Input file name
            case 'i':
            {
                input_file = optarg;
                break;
            }
            // Output file name
            case 'o':
            {
                output_file = optarg;
                break;
            }
            // Unknown
            case '?':
            {
                if (optopt == 'r' || optopt == 'd' || optopt == 'i' || optopt == 'o' || optopt == 's')
                    throw std::runtime_error("Option requires an argument");
                throw std::runtime_error("Unknown option");
                break;
            }
            default:
                throw std::runtime_error("Could not parse commandline options");   
        }
    }
}

}