#ifndef CPP_CONCURR_INCLUDE_LIB_MOD01_M01_6_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD01_M01_6_HPP

#include <thread>
#include <chrono>

namespace concurr {
namespace m01_6 {

using namespace std::chrono_literals;

void foo() {
  std::this_thread::sleep_for(4000ms);
  std::cout << "Hello from foo - " << std::this_thread::get_id() << "\n";
}

void bar() {
  std::this_thread::sleep_for(5000ms);
  std::cout << "Hello from bar - " << std::this_thread::get_id() << "\n";
}

void run() {
  auto foo_thread = std::thread(foo);
  auto bar_thread = std::thread(bar);
  bar_thread.detach();
  std::cout << "This is after bar_thread detach\n";
  foo_thread.join();
  std::cout << "This is after foo_thread join\n";
  std::this_thread::sleep_for(2000ms);
}

}
}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD01_M01_6_HPP