// Module 5: C++ memory model and atomic operations
// 52. Important aspects of memory_order_acquire and memory_order_release

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD05_M05_52_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD05_M05_52_HPP

#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>

namespace concurr::m05_52 {


auto x = std::atomic<bool> { false };
auto y = std::atomic<bool> { false };
auto z = std::atomic<int> { 0 };

void write_x() {
  x.store(true, std::memory_order_release);
}

void write_y() {
  y.store(true, std::memory_order_release);
}

void read_x_then_y() {
  //loop until x is true
  while (!x.load(std::memory_order_acquire)) {
  }
  //check wether y is true
  if (y.load(std::memory_order_acquire)) {
    z++;
  }
}

void read_y_then_x() {
  //loop until y is true
  while (!y.load(std::memory_order_acquire)) {
  }
  //check wether x is true
  if (x.load(std::memory_order_acquire)) {
    z++;
  }
}

void run() {
  auto thread_a = std::thread(write_x);
  auto thread_b = std::thread(write_y);
  auto thread_c = std::thread(read_x_then_y);
  auto thread_d = std::thread(read_y_then_x);

  thread_a.join();
  thread_b.join();
  thread_c.join();
  thread_d.join();

  assert(z != 0);
  std::cout << "z = " << z << "\n";
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD05_M05_52_HPP