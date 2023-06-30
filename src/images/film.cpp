#include "film.hpp"

namespace oingo
{

film::film(std::size_t film_width, std::size_t film_height, std::size_t tile_width, std::size_t tile_height)
    : width(film_width), height(film_height), _pixels(film_width * film_height)
{
    const std::size_t x_tiles = film_width  / tile_width  + static_cast<std::size_t>(film_width  % tile_width  != 0);
    const std::size_t y_tiles = film_height / tile_height + static_cast<std::size_t>(film_height % tile_height != 0);

    for (std::size_t i = 0; i < y_tiles; i++)
        for (std::size_t j = 0; j < x_tiles; j++)
            _tiles.emplace_back(tile{*this, j * tile_width, std::min((j + 1) * tile_width, film_width), i * tile_height, std::min((i + 1) * tile_height, film_height)});

}

film::film(std::size_t film_width, std::size_t film_height)
    : film(film_width, film_height, film_width, film_height)
{
    
}

film::tile::tile(film& f, std::size_t x_min, std::size_t x_max, std::size_t y_min, std::size_t y_max)
    : x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max), _f(f) 
{

}

rgb_view film::tile::operator[](std::size_t i)
{
    const std::size_t width = x_max - x_min;
    return operator()(i % width, i / width);
}

rgb_view film::tile::operator()(std::size_t x, std::size_t y)
{
    return static_cast<rgb_view>(_f(x_min + x, y_min + y));
}

std::size_t film::tile::get_width() const
{
    return x_max - x_min;
}

std::size_t film::tile::get_height() const
{
    return y_max - y_min;
}

float film::tile::get_aspect_ratio() const
{
    return static_cast<float>(get_width()) / static_cast<float>(get_height());
}

std::size_t film::tile::get_film_width()  const
{
    return _f.width;
}

std::size_t film::tile::get_film_height() const
{
    return _f.height;
}

float film::tile::get_film_aspect_ratio() const
{
    return static_cast<float>(_f.width) / static_cast<float>(_f.height);
}

rgb& film::operator[](std::size_t i)
{
    return _pixels[i];
}

rgb& film::operator()(std::size_t x, std::size_t y)
{
    return operator[](y * width + x);
}

const rgb& film::operator[](std::size_t i) const
{
    return _pixels[i];
}

const rgb& film::operator()(std::size_t x, std::size_t y) const
{
    return operator[](y * width + x);
}

film::operator std::span<tile>()
{
    return _tiles;
}

}