// Module 5: C++ memory model and atomic operations
// 47. Introduction to memory ordering options

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD05_M05_47_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD05_M05_47_HPP

#include <iostream>
#include <atomic>

namespace concurr::m05_47 {


void run() {
  auto x = std::atomic<int> {};
  x.store(5, std::memory_order_seq_cst);
  x.store(10, std::memory_order_release);
  std::cout << "x = " << x.load(std::memory_order_acquire) << "\n";

  auto value = int { 10 };
  auto ret_val = x.compare_exchange_weak(value, 11,
                                         std::memory_order_release,
                                         std::memory_order_relaxed);
  std::cout << "exchange successful? - "
            << (ret_val ? "yes" : "no") << "\n";
  std::cout << "x = " << x.load(std::memory_order_acquire) << "\n";
}     

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD05_M05_47_HPP