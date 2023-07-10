#include "thread_pool.hpp"

namespace oingo
{

thread_pool::thread_pool(std::size_t thread_count)
{
    for (std::size_t i = 0; i < thread_count; ++i)
        _threads.emplace_back(&thread_pool::run, this);
}

thread_pool::~thread_pool()
{
    // Stop the loops and notify all the threads
    {
        std::lock_guard<std::mutex> lk(_m);
        _stop = true;
    }
    _c.notify_all();

    // Block until everything is joined
    for (auto& t : _threads)
        t.join();
}

void thread_pool::run()
{
    do
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lk(_m);
            _c.wait(lk, [this] { return _stop || !_tasks.empty(); });
            if (_stop && _tasks.empty())
                return;
            task = std::move(_tasks.front());
            _tasks.pop();
        }
        task();
    }
    while (true);
}

}