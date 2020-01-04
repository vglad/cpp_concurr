// Module 1: Thread management guide
// 10. Problematic situations may arise when passing parameters to a thread

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD01_M01_10_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD01_M01_10_HPP

#include <thread>
#include <iostream>


namespace concurr::m01_10 {

using namespace std::chrono_literals;

void func_2(int& x) {
  while (true) {
    try {
      //after 5 sec it will throw exception here 
      //because x object passes by ref and destroyed in func_1
      //try...catch block not working in this case
      std::cout << x << "\n";
      std::this_thread::sleep_for(500ms);
    } catch (const std::exception&) {
      throw std::runtime_error("Runtime error");
    }
  }
}

void func_1() {
  auto x = int { 5 };
  auto thread_2 = std::thread(func_2, std::ref(x));
  thread_2.detach();
  std::this_thread::sleep_for(5000ms);
  std::cout << "thread_1 finished execution";
}

void run() {
  auto thread_1 = std::thread(func_1);
  thread_1.join();
  std::this_thread::sleep_for(2000ms);
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD01_M01_10_HPP