#ifndef CPP_CONCURR_INCLUDE_LIB_MOD02_M02_21_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD02_M02_21_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <stack>

namespace concurr::m02_21 {

template<typename T>
class triveal_thread_safe_stack {
public:
  void push(T element) {
    auto lg = std::lock_guard<std::mutex>(m);
    stk.push(element);
  }

  void pop() {
    auto lg = std::lock_guard<std::mutex>(m);
    stk.pop();
  }

  T& top() {
    auto lg = std::lock_guard<std::mutex>(m);
    return stk.top();
  }

  bool empty() {
    auto lg = std::lock_guard<std::mutex>(m);
    return stk.empty()
  }
  
  size_t size() {
    auto lg = std::lock_guard<std::mutex>(m);
    auto size = stk.size();
    std::cout << "Size of the stack is: " << size << "\n";
  }

private:
  std::stack<T> stk;
  std::mutex m;

};

class data_object {
public:
  void some_operation() {
    std::cout << "Can change data...\n";
  }
};

class data_wrapper {
public:
  template <typename function>
  void do_some_work(function f) {
    std::lock_guard<std::mutex> lg(m);
    f(protected_data);
  }

private:
  data_object protected_data;
  std::mutex m;
};

data_object* unprotected_data;
void malisious_function(data_object& data) {
  unprotected_data = &data;
}

void run() {
  auto wrapper = data_wrapper {};
  wrapper.do_some_work(malisious_function);
  unprotected_data->some_operation();
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD02_M02_21_HPP