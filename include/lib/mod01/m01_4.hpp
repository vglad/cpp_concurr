#ifndef CPP_CONCURR_INCLUDE_LIB_MOD01_M01_4_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD01_M01_4_HPP

#include <thread>

namespace concurr {
namespace m01_4 {

void test() {
  std::cout << "Hello from test - " << std::this_thread::get_id() << "\n";
}

void fA() {
  auto threadC = std::thread(test);
  threadC.join();
  std::cout << "Hello from A - " << std::this_thread::get_id() << "\n";
}

void fB() {
  std::cout << "Hello from B - " << std::this_thread::get_id() << "\n";
}

void run() {
  auto threadA = std::thread(fA);
  threadA.join();

  auto threadB = std::thread(fB);
  threadB.join();

  std::cout << "Hello from run - " << std::this_thread::get_id() << "\n";
}

}
}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD01_M01_4_HPP