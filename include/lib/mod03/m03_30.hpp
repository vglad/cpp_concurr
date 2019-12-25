#ifndef CPP_CONCURR_INCLUDE_LIB_MOD03_M03_30_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD03_M03_30_HPP

#include <iostream>
#include <string>
#include <future>

namespace concurr::m03_30 {

void printing() {
  std::cout << "printing runs on: " << std::this_thread::get_id() << "\n";
}

int addition(int x, int y) {
  std::cout << "addition runs on: " << std::this_thread::get_id() << "\n";
  return x + y;
}

int subtract(int x, int y) {
  std::cout << "subtraction runs on: " << std::this_thread::get_id() << "\n";
  return x - y;
}

void run() {
  std::cout << "main thread id: " << std::this_thread::get_id() << "\n";

  auto x = 100;
  auto y = 50;

  auto f1 = std::async(std::launch::async, printing);
  auto f2 = std::async(std::launch::deferred, addition, x, y);
  auto f3 = std::async(std::launch::deferred | std::launch::async, subtract, x, y);

  f1.get();
  std::cout << "value recieved using f2 future: " << f2.get() << "\n";
  std::cout << "value recieved using f3 future: " << f3.get() << "\n";

}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD03_M03_30_HPP