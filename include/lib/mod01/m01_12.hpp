// Module 1: Thread management guide
// 12. Some useful operations on thread

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD01_M01_12_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD01_M01_12_HPP

#include <thread>
#include <iostream>

namespace concurr::m01_12 {

void bar() {
  std::cout << "Hello from bar - " << std::this_thread::get_id() << "\n";
}

void foo() {
  std::cout << "Hello from foo - " << std::this_thread::get_id() << "\n";
}

void run() {
  auto thread_1 = std::thread(foo);
  auto thread_2 = std::thread(foo);
  auto thread_3 = std::thread(foo);
  auto thread_4 = std::thread();

  std::cout << "\n";
  std::cout << "thread_1 id: " << thread_1.get_id() << "\n";
  std::cout << "thread_2 id: " << thread_2.get_id() << "\n";
  std::cout << "thread_3 id: " << thread_3.get_id() << "\n";
  std::cout << "thread_4 id: " << thread_4.get_id() << "\n";

  thread_1.join();
  thread_2.join();
  thread_3.join();

  std::cout << "thread_3 id after join(): " << thread_3.get_id() << "\n";

  auto allowed_threads = std::thread::hardware_concurrency();
  std::cout << "Allowed thread count on this device: " << allowed_threads << "\n";

}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD01_M01_12_HPP