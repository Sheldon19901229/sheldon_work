
#ifndef SAFE_QUEUE_H
#define SAFE_QUEUE_H

#include <vector>
#include <deque>
#include <mutex>
#include <condition_variable>

template <typename T>
class SafeQueue {
public:
    SafeQueue() : eoq_(false), max_len_(safe_queue_default_max_len) {}

    SafeQueue(const SafeQueue& other) {
        std::lock_guard<std::mutex> lk(other.mut_);
        que_     = other.que_;
        eoq_     = other.eoq_;
        max_len_ = other.max_len_;
    }

    template <typename _InputIterator>
    SafeQueue(_InputIterator first, _InputIterator last) {
        for (auto it = first; it != last; ++it) {
            que_->emplace_back(it);
        }
        eoq_     = false;
        max_len_ = safe_queue_default_max_len;
    }

    SafeQueue(SafeQueue const&& other) {
        std::lock_guard<std::mutex> lk(other.mut_);
        que_     = std::move(other.que_);
        eoq_     = other.eoq_;
        max_len_ = other.max_len_;
    }

    ~SafeQueue() {
        stop();
    }

    /**
     * @brief 插入一个元素
     * @param new_value 新元素
     */
    void force_push(const T& new_value) {
        std::lock_guard<std::mutex> lk(mut_);
        if (!eoq_) {
            que_.emplace_back(new_value);
            eoq_ = false;
            cond_pop_.notify_one();
        }
    }

    /**
     * @brief 将整个vector<T>线程安全的压入队列
     * @param vec 数据序列
     */
    void force_push(std::vector<T>& vec) {
        std::lock_guard<std::mutex> lk(mut_);
        if (!eoq_) {
            std::copy(vec.begin(), vec.end(), std::back_inserter(que_));
            eoq_ = false;
            cond_pop_.notify_one();
        }
    }

    /**
     * @brief 将bg~ed迭代器的内容线程安全的压入队列
     * @param bg 起始迭代器
     * @param ed 结束迭代器
     */
    template <typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>>
    void force_push(_InputIterator bg, _InputIterator ed) {
        std::lock_guard<std::mutex> lk(mut_);
        if (!eoq_) {
            for (auto it = bg; it != ed; ++it) {
                que_.emplace_back(*it);
            }
            eoq_ = false;
            cond_pop_.notify_one();
        }
    }

    /**
     * @brief 尝试插入一个元素
     * @param new_value 新元素
     * @return true 成功插入
     * @return false 超过设定的队列长度
     */
    bool try_push(const T& new_value) {
        std::lock_guard<std::mutex> lk(mut_);
        if (!eoq_ && max_len_ > 0 && que_.size() < max_len_) {
            que_.emplace_back(new_value);
            eoq_ = false;
            cond_pop_.notify_one();
            return true;
        }
        return false;
    }

    /**
     * @brief 尝试将整个vector<T>线程安全的压入队列
     * @param vec 数据序列
     * @return true 成功插入
     * @return false 超过设定的队列长度
     */
    bool try_push(const std::vector<T>& vec) {
        std::lock_guard<std::mutex> lk(mut_);
        if (!eoq_ && max_len_ > 0 && que_.size() + vec.size() < max_len_) {
            std::copy(vec.begin(), vec.end(), std::back_inserter(que_));
            eoq_ = false;
            cond_pop_.notify_one();
            return true;
        }
        return false;
    }

    /**
     * @brief 尝试将bg~ed迭代器的内容线程安全的压入队列
     * @param bg 起始迭代器
     * @param ed 结束迭代器
     * @return true 成功插入
     * @return false 超过设定的队列长度
     */
    template <typename _InputIterator, typename = std::_RequireInputIter<_InputIterator>>
    bool try_push(_InputIterator bg, _InputIterator ed) {
        std::lock_guard<std::mutex> lk(mut_);
        if (!eoq_ && max_len_ > 0 && que_.size() + (ed - bg) < max_len_) {
            for (auto it = bg; it != ed; ++it) {
                que_.emplace_back(*it);
            }
            eoq_ = false;
            cond_pop_.notify_one();
            return true;
        }
        return false;
    }

    /**
     * @brief 等待并插入一个元素
     * @param new_value 新元素
     */
    void wait_and_push(const T& new_value) {
        std::unique_lock<std::mutex> lk(mut_);
        while (!eoq_) {
            cond_push_.wait(
                lk, [this] { return eoq_ || (max_len_ == 0 || que_.size() < max_len_); });
            if (max_len_ == 0 || que_.size() < max_len_) {
                que_.emplace_back(new_value);
                eoq_ = false;
                cond_pop_.notify_one();
                return;
            }
        }
    }

    /**
     * @brief 在首位插入一个元素
     * @param new_value 新元素
     */
    void push_front(const T& new_value) {
        std::lock_guard<std::mutex> lk(mut_);
        que_.emplace_front(new_value);
        eoq_ = false;
        cond_pop_.notify_one();
    }

    /**
     * @brief 等待直到有元素可以删除为止
     * @param value 弹出的元素
     * @return true 成功弹出
     * @return false 队列关闭，获取失败
     */
    bool wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut_);
        while (!eoq_) {
            cond_pop_.wait(lk, [this] { return eoq_ || !que_.empty(); });
            if (!que_.empty()) {
                value = std::move(que_.front());
                que_.pop_front();
                cond_push_.notify_one();
                return true;
            }
        }
        return false;
    }

    /**
     * @brief 等待直到有元素可以删除为止
     * @return std::shared_ptr<T> 元素的指针
     */
    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lk(mut_);
        while (!eoq_) {
            cond_pop_.wait(lk, [this] { return eoq_ || !que_.empty(); });
            if (!que_.empty()) {
                std::shared_ptr<T> res(std::make_shared<T>(que_.front()));
                que_.pop_front();
                cond_push_.notify_one();
                return res;
            }
        }
        return nullptr;
    }

    /**
     * @brief 不等待返回元素
     * @param value 返回的值
     * @return true 成功返回
     * @return false 返回失败
     */
    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lk(mut_);
        if (que_.empty())
            return false;
        value = std::move(que_.front());
        que_.pop_front();
        cond_push_.notify_one();
        return true;
    }

    /**
     * @brief 不等待返回元素
     * @return std::shared_ptr<T> 返回元素的指针
     */
    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lk(mut_);
        if (que_.empty())
            return nullptr;
        std::shared_ptr<T> res(std::make_shared<T>(que_.front()));
        que_.pop_front();
        cond_push_.notify_one();
        return res;
    }

    /**
     * @brief 判断队列是否为空
     * @return true 空队列
     * @return false 队列非空
     */
    bool empty() const {
        std::lock_guard<std::mutex> lk(mut_);
        return que_.empty();
    }

    /**
     * @brief 返回队列长度
     * @return size_t 队列长度
     */
    size_t size() const {
        std::lock_guard<std::mutex> lk(mut_);
        return que_.size();
    }

    /**
     * @brief 关闭队列，队列会取消所有阻塞，此时队列已经失效
     */
    void stop() {
        std::lock_guard<std::mutex> lk(mut_);
        eoq_ = true;
        cond_push_.notify_all();
        cond_pop_.notify_all();
    }

    /**
     * @brief 队列是否可用
     *
     * @return true 可用
     * @return false 不可用
     */
    bool enable() {
        std::lock_guard<std::mutex> lk(mut_);
        return !eoq_;
    }

    /**
     * @brief 重置队列，失效队列恢复
     */
    void reset() {
        std::lock_guard<std::mutex> lk(mut_);
        que_.clear();
        eoq_ = false;
        cond_push_.notify_all();
        cond_pop_.notify_all();
    }

    /**
     * @brief 将队列内容移动到vector<T>中
     * @param vec 接收的队列vector<T>
     */
    void move2vec(std::vector<T>* vec) {
        std::lock_guard<std::mutex> lk(mut_);
        for (auto it = que_.begin(); it != que_.end(); ++it) {
            vec->emplace_back(*it);
        }
        que_.clear();
        eoq_ = false;
    }

    /**
     * @brief 将队列长度规整为指定长度（头部元素被丢弃）
     * @param len 规整长度
     */
    void trim(int len) {
        std::lock_guard<std::mutex> lk(mut_);
        while (que_.size() > len) {
            que_.pop_front();
        }
    }

    void set_max_len(unsigned int len) {
        std::lock_guard<std::mutex> lk(mut_);
        max_len_ = len;
    }

    const unsigned int max_len() {
        return max_len_;
    }

private:
    mutable std::mutex      mut_;
    std::deque<T>           que_;
    std::condition_variable cond_pop_;
    std::condition_variable cond_push_;
    bool                    eoq_;
    unsigned int            max_len_;
    static const int        safe_queue_default_max_len = 3;
};

#endif