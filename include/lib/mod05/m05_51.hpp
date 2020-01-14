// Module 5: C++ memory model and atomic operations
// 51. Discussion on memory_order_acquire and memory_order_release

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD05_M05_51_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD05_M05_51_HPP

#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>

namespace concurr::m05_51 {


auto x = std::atomic<bool> { false };
auto y = std::atomic<bool> { false };
auto z = std::atomic<int> { 0 };

void write_x_then_y() {
  x.store(true, std::memory_order_relaxed);
  y.store(true, std::memory_order_release);
}


void read_y_then_x() {
  //loop until y is true
  while (!y.load(std::memory_order_acquire)) {
  }
  //check wether x is true
  if (x.load(std::memory_order_relaxed)) {
    z++;
  }
}

void run() {
  auto thread_writer = std::thread(write_x_then_y);
  auto thread_reader = std::thread(read_y_then_x);

  thread_writer.join();
  thread_reader.join();

  assert(z != 0);
  std::cout << "z = " << z << "\n";
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD05_M05_51_HPP