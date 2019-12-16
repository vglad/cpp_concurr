#ifndef CPP_CONCURR_INCLUDE_LIB_MOD01_M01_07_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD01_M01_07_HPP

#include <thread>
#include <iostream>

#include "ThreadGuard.hpp"

namespace concurr {
namespace m01_07 {

void foo() {
  std::cout << "Hello from foo - " << std::this_thread::get_id() << "\n";
}

void other_operations() {
  std::cout << "This is other operations that throw\n";
  throw std::runtime_error("Runtime error");
}


void run() {
  //auto foo_thread = std::thread(foo);
  //try {
  //  other_operations();
  //  foo_thread.join();
  //} catch (...) {
  //  foo_thread.join();
  //}
  
  auto foo_thread = std::thread(foo);
  auto tg         = detail::thread_guard(foo_thread);
  try {
    other_operations();
  } catch (const std::exception&) {
  }
}

}
}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD01_M01_07_HPP