#include "depth_counter.hpp"

namespace oingo
{

std::size_t depth_counter::get_depth() const noexcept
{
    return _depth;
}

depth_counter::incrementer::incrementer(depth_counter& counter)
    : _counter(counter)
{
    _counter._depth++;
}

depth_counter::incrementer::~incrementer()
{
    _counter._depth--;  
}

depth_counter::incrementer depth_counter::increment()
{
    return incrementer(*this);
}

}