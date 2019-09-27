#ifndef _QUEUE_TS_H
#define _QUEUE_TS_H

#include <mutex>
#include <list>
#include <memory>
#include <condition_variable>

template<typename T>
class QueueTs {
  std::list< std::shared_ptr<T> > buf_;
  mutable std::mutex mutex_;
  std::condition_variable data_cond_;
 public:
  int Size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return buf_.size();
  }
  
  bool Empty() const {
    return Size() == 0;
  }
  
  void Push(T obj) {
    std::shared_ptr<T> data(std::make_shared<T>(std::move(obj)));
    std::lock_guard<std::mutex> lock(mutex_);
    buf_.push_back(data);
    data_cond_.notify_one();
  }
  
  T Pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    data_cond_.wait(lock, [this]{return !buf_.empty();});
    std::shared_ptr<T> res = buf_.front();
    buf_.pop_front();
    return *res;
  }

  bool TryPop(T & value) {
    std::unique_lock<std::mutex> lock(mutex_);
    if (buf_.empty()) {
      return false;
    }
    value = std::move(*buf_.front());
    buf_.pop_front();
    return true;
  }
  
//   std::shared_ptr<T> Pop() {
//     std::unique_lock<std::mutex> lock(mutex_);
//     data_cond_.wait(lock, [this]{return !buf_.empty();});
//     std::shared_ptr<T> res = buf_.front();
//     buf_.pop_front();
//     return res;
//   }
};

#endif //_QUEUE_TS_H
