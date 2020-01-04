// Module 2: Thread safe access to shared data and locking mechanisms
// 22. Thread safe stack implementation: race condition inherit from the interface

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD02_M02_22_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD02_M02_22_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <stack>

namespace concurr::m02_22 {

template<typename T>
class thread_safe_stack {
public:
  void push(T element) {
    auto lg = std::lock_guard<std::mutex>(m);
    stk.push(std::make_shared<T>(element));
  }

  std::shared_ptr<T> pop() {
    auto lg = std::lock_guard<std::mutex>(m);
    if (stk.empty()) {
      throw std::runtime_error("Calling pop on empty stack\n");
    }
    auto result = std::shared_ptr<T>(stk.top());
    stk.pop();
    return result;
  }

  void pop(T& value) {
    auto lg = std::lock_guard<std::mutex>(m);
    if (stk.empty()) {
      throw std::runtime_error("Calling pop on empty stack\n");
    }
    value = *(stk.top().get());
    stk.pop();
  }

  bool empty() {
    auto lg = std::lock_guard<std::mutex>(m);
    return stk.empty();
  }
  
  size_t size() {
    auto lg = std::lock_guard<std::mutex>(m);
    return stk.size();

  }

private:
  std::stack<std::shared_ptr<T>> stk;
  std::mutex m;

};

auto stk = thread_safe_stack<int> {};

void func_1() {
  if (!stk.empty()) {
    //int value = *(stk.pop().get());
    auto value = 0;
    stk.pop(value);
    std::cout << "Value: " << value << "\n";
  } else {
    std::cout << "Calling pop on empty stack\n";
  }
}


void run() {
  stk.push(1);
  stk.push(2);

  auto thread_1 = std::thread(func_1);
  auto thread_2 = std::thread(func_1);
  auto thread_3 = std::thread(func_1);

  thread_1.join();
  thread_2.join();
  thread_3.join();

  if (stk.empty()) {
    std::cout << "\nStack is now empty \n";
  }
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD02_M02_22_HPP