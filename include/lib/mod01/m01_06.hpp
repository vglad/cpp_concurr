#ifndef CPP_CONCURR_INCLUDE_LIB_MOD01_M01_06_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD01_M01_06_HPP

#include <thread>
#include <chrono>
#include <iostream>

namespace concurr::m01_06 {

using namespace std::chrono_literals;

void foo() {
  std::this_thread::sleep_for(4s);
  std::cout << "Hello from foo - " << std::this_thread::get_id() << "\n";
}

void bar() {
  std::this_thread::sleep_for(5s);
  std::cout << "Hello from bar - " << std::this_thread::get_id() << "\n";
}

void run() {
  auto foo_thread = std::thread(foo);
  auto bar_thread = std::thread(bar);
  bar_thread.detach();
  std::cout << "This is after bar_thread detach\n";
  foo_thread.join();
  std::cout << "This is after foo_thread join\n";
  std::this_thread::sleep_for(2s);
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD01_M01_06_HPP