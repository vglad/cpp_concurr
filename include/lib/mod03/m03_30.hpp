// Module 3: Communication between threads using condition variables and futures
// 30. Async tasks detailed discussion

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD03_M03_30_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD03_M03_30_HPP

#include <iostream>
#include <string>
#include <future>

namespace concurr::m03_30 {

void printing() {
  std::cout << "printing runs on: " << std::this_thread::get_id() << "\n";
}

int64_t addition(int64_t x, int64_t y) {
  std::cout << "addition runs on: " << std::this_thread::get_id() << "\n";
  return x + y;
}

int64_t subtract(int64_t x, int64_t y) {
  std::cout << "subtraction runs on: " << std::this_thread::get_id() << "\n";
  return x - y;
}

void run() {
  std::cout << "main thread id: " << std::this_thread::get_id() << "\n";

  auto const x = int64_t { 100 };
  auto const y = int64_t { 50 };

  auto f1 = std::async(std::launch::async, printing);
  auto f2 = std::async(std::launch::deferred, addition, x, y);
  auto f3 = std::async(std::launch::deferred | std::launch::async, subtract, x, y);

  f1.get();
  std::cout << "value recieved using f2 future: " << std::to_string(f2.get()) << "\n";
  std::cout << "value recieved using f3 future: " << std::to_string(f3.get()) << "\n";

}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD03_M03_30_HPP