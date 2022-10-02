#include "render/simple_sampler.hpp"
#include "cameras/digital.hpp"
#include "objects/sphere.hpp"

#include <iostream>

using namespace oingo;

int main()
{
    scene::scene s;

    std::unique_ptr<cameras::digital> c = std::make_unique<cameras::digital>();
    s.cam = std::move(c);

    std::unique_ptr<objects::sphere> obj = std::make_unique<objects::sphere>();
    obj->translate({ 5, 0, 0 });
    s.objects.emplace_back(std::move(obj));

    film f(480, 270);

    render::simple_sampler r;
    r.render(s, f, std::cout);

    return EXIT_SUCCESS;
}