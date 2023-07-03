#pragma once

#include <cstddef>

namespace oingo
{
    
// Make a static thread local one of these to keep track of the depth of the
// recursion (e.g. for ray bouncing)
class depth_counter
{
public:
    std::size_t get_depth() const noexcept;

    class incrementer
    {
    public:
        incrementer(const incrementer&) = delete;
        incrementer& operator=(const incrementer&) = delete;

        incrementer(incrementer&&) = delete;
        incrementer& operator=(incrementer&&) = delete;

        ~incrementer();

    private:
        incrementer(depth_counter& counter);

        friend class depth_counter;
        depth_counter& _counter;
    };

    incrementer increment();

private:
    friend class incrementer;
    std::size_t _depth { 0 };
};

}