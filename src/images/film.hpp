#pragma once

#include "rgb.hpp"

#include <span>
#include <vector>

namespace oingo
{

class film
{
public:
    film(std::size_t film_width, std::size_t film_height, std::size_t tile_width, std::size_t tile_height);
    film(std::size_t film_width, std::size_t film_height);
    
    const std::size_t width;
    const std::size_t height;

    class tile
    {
    private:
        tile(film& f, std::size_t x_min, std::size_t x_max, std::size_t y_min, std::size_t y_max);
        tile(const tile&) = delete;
        tile& operator=(const tile&) = delete;

        friend class film;
    
    public:
        tile(tile&&) = default;
        tile& operator=(tile&&) = default;
        ~tile() = default;

        rgb_view operator[](std::size_t i);
        rgb_view operator()(std::size_t x, std::size_t y);

        std::size_t get_width() const;
        std::size_t get_height() const;
        float get_aspect_ratio() const;

        std::size_t get_film_width()  const;
        std::size_t get_film_height() const;
        float get_film_aspect_ratio() const;

        const std::size_t x_min;
        const std::size_t x_max;
        const std::size_t y_min;
        const std::size_t y_max;

    private:
        film& _f;
    };

    rgb& operator[](std::size_t i);
    rgb& operator()(std::size_t x, std::size_t y);
    
    const rgb& operator[](std::size_t i) const;
    const rgb& operator()(std::size_t x, std::size_t y) const;

    explicit operator std::span<tile>();

private:
    std::vector<tile> _tiles;
    std::vector<rgb>  _pixels;
};

}