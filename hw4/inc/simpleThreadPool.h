#pragma once
#include <iostream>
#include <vector>
#include<future>
#include<queue>
#include<thread>
#include<condition_variable>
#include <memory>

using namespace std;


/**
 * @brief !!!Pls note that I didn't finish implementation, this solution does not work as expected.
 */


class SimpleThreadPool {
public:
    explicit SimpleThreadPool(std::size_t threadCount): m_threadCount(threadCount), stop(false) {
        threads.reserve(m_threadCount);
        for (size_t indx = 0; indx < m_threadCount; ++indx) {
            threads.emplace_back(&SimpleThreadPool::WorkOn, this);
        }
    };

    ~SimpleThreadPool() = default;
    SimpleThreadPool(const SimpleThreadPool & ) = delete;
    SimpleThreadPool & operator = (const SimpleThreadPool & ) = delete;

    template <typename Fnc_T>
    auto Post(Fnc_T task) -> std::future <decltype(task())> {

        auto pkgTask = std::make_shared<std::packaged_task<void()>>(task);
        std::unique_lock<std::mutex> lock(mut);
        tasks.emplace(std::forward<Fnc_T>(task));

        if(stop) throw std::runtime_error("ThreadPool was stoped!");
        condition.notify_one();
        return pkgTask->get_future();
    }

    void WorkOn() {
        while (true)
        {
            std::function<void()> task;
            {
                std::unique_lock lock(mut);
                condition.wait(lock, [this]() { return stop || !tasks.empty(); });
                if (stop && tasks.empty()) {
                    return;
                }

                task = std::move(tasks.front());
                tasks.pop();
            }
            task();
        }
    }
    void Destroy() {
        {
            std::unique_lock<std::mutex> lock(mut);
            stop = true;
        }
        condition.notify_all();
        for(std::thread &th: threads){
            th.join();
        }
    }

private:
    size_t m_threadCount;
    std::vector <std::thread> threads;
    std::queue <std::function <void()>> tasks;
    std::condition_variable condition;
    std::mutex mut;
    bool stop;
};
