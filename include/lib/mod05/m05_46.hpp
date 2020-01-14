// Module 5: C++ memory model and atomic operations
// 46. Important relationships related to atomic operations between threads

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD05_M05_46_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD05_M05_46_HPP

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

namespace concurr::m05_46 {

using namespace std::chrono_literals;

auto data_ready  = std::atomic<bool> { false };
auto data_vector = std::vector<int> {};

void reader_func() {
  while (!data_ready) {
    std::this_thread::sleep_for(500ms);
  }
  std::cout << data_vector[0] << "\n";
}

void writer_func() {
  data_vector.emplace_back(3);
  data_ready.store(true);
}



void run() {
  auto reader_thread = std::thread(reader_func);
  auto writer_thread = std::thread(writer_func);

  reader_thread.join();
  writer_thread.join();
}     

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD05_M05_46_HPP