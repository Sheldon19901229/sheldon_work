#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class threadPool {
public:
    threadPool(size_t thread_num);
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;
    ~threadPool();
private:
    std::vector<std::thread> workers; // 线程列表
    std::queue<std::function<void()>> tasks; // 任务列表
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

// 初始线程池
inline threadPool::threadPool(size_t thread_num) : stop(false) {
    for(auto i = 0; i < thread_num; ++i) {
        workers.emplace_back([this] {
            for(;;) {
                std::function<void()> task;
                {
                    // 取出任务
                    std::unique_lock<std::mutex> lock(this->queue_mutex);
                    this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                    if (this->stop && this->tasks.empty())
                        return;
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                // 执行
                task();
            }
        });
    }
}

// 添加任务
template<class F, class... Args>
auto threadPool::enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;
    // 创建1个返回值为return_type,参数为空的packaged_task对象,方便异步调用
    auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if(stop) throw std::runtime_error("enqueue on stopped threadPool");
        tasks.emplace([task](){ (*task)(); }); // 将task对象封装成lambda表达式放入任务列表
    }
    condition.notify_one();
    return res;
}

inline threadPool::~threadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread &worker: workers) worker.join();
}

#endif