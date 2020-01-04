// Module 1: Thread management guide
// 11. Transferring ownership of a thread

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD01_M01_11_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD01_M01_11_HPP

#include <thread>
#include <iostream>

namespace concurr::m01_11 {

void bar() {
  std::cout << "Hello from bar\n";
}

void foo() {
  std::cout << "Hello from foo\n";
}

void run() {
  auto thread_1 = std::thread(foo);
  auto thread_2 = std::move(thread_1);

  thread_1 = std::thread(bar);

  auto thread_3 = std::thread(foo);

  //exception thrown here because we trying to move thread
  //into thread object that already own different thread
  thread_1 = std::move(thread_3);

  thread_1.join();
  thread_2.join();
  thread_3.join();
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD01_M01_11_HPP