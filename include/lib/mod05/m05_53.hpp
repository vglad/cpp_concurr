// Module 5: C++ memory model and atomic operations
// 53. Concept of transitive synchronization

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD05_M05_53_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD05_M05_53_HPP

#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>

std::atomic<int> data[5];
auto sync1 = std::atomic<bool> { false };
auto sync2 = std::atomic<bool> { false };


namespace concurr::m05_53 {

void thread1_func() {
  data[0].store(42, std::memory_order_relaxed);
  data[1].store(45, std::memory_order_relaxed);
  data[2].store(47, std::memory_order_relaxed);
  data[3].store(49, std::memory_order_relaxed);
  data[4].store(56, std::memory_order_relaxed);
  sync1.store(true, std::memory_order_release);

}

void thread2_func() {
  while (!sync1.load(std::memory_order_acquire)) {
  }
  sync2.store(true, std::memory_order_release);
}

void thread3_func() {
  while (!sync2.load(std::memory_order_acquire)) {
  }
  assert(data[0].load(std::memory_order_relaxed) == 42);
  assert(data[1].load(std::memory_order_relaxed) == 45);
  assert(data[2].load(std::memory_order_relaxed) == 47);
  assert(data[3].load(std::memory_order_relaxed) == 49);
  assert(data[4].load(std::memory_order_relaxed) == 56);
}


void run() {
  auto thr1 = std::thread(thread1_func);
  auto thr2 = std::thread(thread2_func);
  auto thr3 = std::thread(thread3_func);

  thr1.join();
  thr2.join();
  thr3.join();

}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD05_M05_53_HPP