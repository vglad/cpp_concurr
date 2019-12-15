#ifndef CPP_CONCURR_INCLUDE_LIB_MOD01_M01_9_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD01_M01_9_HPP

#include <iostream>
#include <thread>
#include <functional>

namespace concurr {
namespace m01_9 {

using namespace std::chrono_literals;

void func_1(int x, int y) {
  std::cout << "X + Y = " << x + y << "\n";
}

void func_2(int & x) {
  for (;;) {
    std::cout << "thread_1 value of X - " << x << "\n";
    std::this_thread::sleep_for(1000ms);
  }
}

void run() {
  //auto p = uint8_t { 9 }, q = uint8_t { 8 };
  //auto thread_1 = std::thread(func_1, p, q);
  //thread_1.join();

  auto x = int { 9 };
  std::cout << "thread_1 value of X - " << std::to_string(x) << "\n";

  auto thread_1 = std::thread(func_2, std::ref(x));
  std::this_thread::sleep_for(4000ms);

  x = 15;
  std::cout << "thread_1 value of X changed to - " << x << "\n";
  thread_1.join();


}

}
}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD01_M01_9_HPP