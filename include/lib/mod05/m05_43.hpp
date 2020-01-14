// Module 5: C++ memory model and atomic operations
// 43. Explanation of compare_exchange functions

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD05_M05_43_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD05_M05_43_HPP

#include <iostream>
#include <atomic>

namespace concurr::m05_43 {

void run() {
  auto x        = std::atomic<int> { 20 };
  auto expected = int { 20 };
  std::cout << "previous expected value: " << expected << "\n";
  auto return_val = x.compare_exchange_weak(expected, 6);
  std::cout << "operation successful: " << (return_val ? "yes" : "no") << "\n";
  std::cout << "current expected value: " << expected << "\n";
  std::cout << "current x value: " << x.load() << "\n";

  x.store(20);
  expected = 10;
  std::cout << "previous expected value: " << expected << "\n";
  return_val = x.compare_exchange_strong(expected, 6);
  std::cout << "operation successful: " << (return_val ? "yes" : "no") << "\n";
  std::cout << "current expected value: " << expected << "\n";
  std::cout << "current x value: " << x.load() << "\n";


}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD05_M05_43_HPP