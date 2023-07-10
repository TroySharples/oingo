#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>

namespace oingo
{

class thread_pool
{
public:
    thread_pool(std::size_t thread_count = 0);
    ~thread_pool();

    thread_pool(const thread_pool&) = delete;
    thread_pool& operator=(const thread_pool&) = delete;

    thread_pool(thread_pool&&) = delete;
    thread_pool& operator=(thread_pool&&) = delete;

    template <typename F, typename... Args>
    void enqueue(F&& t, Args&&... args);

private:
    std::mutex _m;
    bool _stop {false};
    std::queue<std::function<void()>> _tasks;
    std::condition_variable _c;

    std::vector<std::thread> _threads;

private:
    void run();
};

template <typename F, typename... Args>
void thread_pool::enqueue(F&& t, Args&&... args)
{
    // Add to the task queue and notify a single thread
    {
        std::lock_guard<std::mutex> lk(_m);
        if (_stop)
            return;
        _tasks.emplace(std::bind(std::forward<F>(t), std::forward<Args>(args)...));
    }
    _c.notify_one();
}

}