#pragma once

#include <functional>
#include <string_view>
#include <string>
#include <chrono>
#include <atomic>
#include <memory>

class life_timer
{
public:
    life_timer(std::string_view label);
    life_timer(std::function<void(double)> callback);
    ~life_timer();

private:
    const std::chrono::system_clock::time_point _start_time { std::chrono::system_clock::now() };
    
    const std::function<void(double)> _callback;
};

class total_timer
{
public:
    total_timer(std::string_view label);
    ~total_timer();
    
    std::unique_ptr<life_timer> add_timer();
    
private:
    std::atomic<double> _total_time = 0;
    
    const std::string _label;
    
private:
    void add_time(double time);
};
