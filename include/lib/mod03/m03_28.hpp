// Module 3: Communication between threads using condition variables and futures
// 28. Thread safe queue implementation: implementation

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD03_M03_28_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD03_M03_28_HPP

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>

namespace concurr::m03_28 {

using namespace std::chrono_literals;

template<typename T>
class thread_safe_queue {

public:
  thread_safe_queue() {
  }

  thread_safe_queue(thread_safe_queue const& other) {
    auto lg = std::lock_guard<std::mutex>(other.m);
    queue = other.queue;
  }

  void push(T const & value) {
    auto lg = std::lock_guard<std::mutex>(m);
    queue.push(std::make_shared<T>(value));
    cv.notify_one();
  }

  std::shared_ptr<T> pop() {
    auto lg = std::lock_guard<std::mutex>(m);
    if (!queue.empty()) {
      return std::shared_ptr<T>();
    } else {
      auto ref = std::shared_ptr<T>(queue.front());
      queue.pop();
      return ref;
    }
  }

  bool pop(T& ref) {
    auto lg = std::lock_guard<std::mutex>(m);
    if (queue.empty()) {
      return false;
    } else {
      ref = *(queue.front());
      queue.pop();
      return true;
    }
  }

  std::shared_ptr<T> wait_pop() {
    auto lg = std::unique_lock<std::mutex>(m);
    cv.wait(lg, [this] { return !queue.empty(); });
    auto ref = std::shared_ptr<T>(queue.front());
    queue.pop();
    return ref;
  }

  bool wait_pop(T& ref) {
    auto lg = std::unique_lock<std::mutex>(m);
    cv.wait(lg, [this] { return !queue.empty(); });
    ref = *(queue.front());
    queue.pop();
    return true;
  }

  bool empty() {
    auto lg = std::lock_guard<std::mutex>(m);
    return queue.empty();
  }

  size_t size() {
    auto lg = std::lock_guard<std::mutex>(m);
    return queue.size();
  }

private:
  std::mutex m;
  std::condition_variable cv;
  std::queue<std::shared_ptr<T>> queue;

};

auto q = thread_safe_queue<int> {};

void func_1() {
  if (!q.empty()) {
    //int value = *(stk.pop().get());
    auto value = 0;
    q.pop(value);
    std::cout << "Value: " << value << "\n";
  } else {
    std::cout << "Calling pop on empty queue\n";
  }
}

void run() {
  auto n1 = 1;
  auto n2 = 2;
  q.push(n1);
  q.push(n2);

  auto thread_1 = std::thread(func_1);
  auto thread_2 = std::thread(func_1);
  auto thread_3 = std::thread(func_1);

  thread_1.join();
  thread_2.join();
  thread_3.join();


}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD03_M03_28_HPP