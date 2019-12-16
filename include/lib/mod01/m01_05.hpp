#ifndef CPP_CONCURR_INCLUDE_LIB_MOD01_M01_05_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD01_M01_05_HPP

#include <thread>
#include <iostream>

namespace concurr {
namespace m01_05 {

void test() {
  std::cout << "Hello from test - " << std::this_thread::get_id() << "\n";
}

void run() {
  std::cout << "Properly constructed thread is joinable\n";
  auto thread1 = std::thread(test);

  if (thread1.joinable()) {
    std::cout << "Thread1 is joinable before join() call\n";
  } else {
    std::cout << "Thread1 is not joinable before join() call\n";
  }

  thread1.join();

  if (thread1.joinable()) {
    std::cout << "Thread1 is joinable after join() call\n";
  } else {
    std::cout << "Thread1 is not joinable after join() call\n";
  }

  std::cout << "\nNot properly constructed thread is not joinable\n";
  auto thread2 = std::thread();

  if (thread2.joinable()) {
    std::cout << "Thread2 is joinable\n";
  } else {
    std::cout << "Thread2 is not joinable\n";
  }
}

}
}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD01_M01_05_HPP