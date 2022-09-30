#include "timer.hpp"

#include "logging/console.hpp"

#include <iostream>

static void default_callback(std::string label, double time)
{
    PRINT_TIME("Life timer \"" << label << "\" - " << time << " ms");
}

life_timer::life_timer(std::string_view label)
    : _callback(std::bind(default_callback, std::string(label), std::placeholders::_1))
{
    
}

life_timer::life_timer(std::function<void(double)> callback)
    : _callback(callback)
{
    
}

life_timer::~life_timer()       
{
    const double duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _start_time).count();
    _callback(duration);
}

total_timer::total_timer(std::string_view label)
    : _label(label)
{
    
}

total_timer::~total_timer()
{
    PRINT_TIME("Total timer \"" << _label << "\" - " << _total_time << " ms");
}

std::unique_ptr<life_timer> total_timer::add_timer()
{
    return std::make_unique<life_timer>(std::bind(&total_timer::add_time, this, std::placeholders::_1));
}

void total_timer::add_time(double time)
{
    _total_time += time;
}