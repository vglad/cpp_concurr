// Module 3: Communication between threads using condition variables and futures
// 34. Retrieving exception using std::futures

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD03_M03_34_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD03_M03_34_HPP

#include <iostream>
#include <future>
#include <thread>

namespace concurr::m03_34 {

using namespace std::chrono_literals;

void throw_exception() {
  throw  std::invalid_argument("input can not be negative");
}

void calculate_square_root(std::promise<double>& prom) {
  auto x = int { 0 };
  std::cout << "Please enter an integer value: \n";
  try {
    std::cin >> x;
    if (x < 0) {
      throw_exception();
    }
    prom.set_value(std::sqrt(x));
  } catch (std::exception const&) {
    prom.set_exception(std::current_exception());
  }
}

void print_result(std::future<double>& fut) {
  try {
    auto x = fut.get();
    std::cout << "value: " << x << "\n";
  }
  catch (std::exception const& e) {
    std::cout << "[exception caught: " << e.what() << "]\n";
  }
}

void run() {
  auto prom = std::promise<double>();
  auto fut  = prom.get_future();

  auto printing_thread    = std::thread(print_result, std::ref(fut));
  auto calculation_thread = std::thread(calculate_square_root, std::ref(prom));

  printing_thread.join();
  calculation_thread.join();

}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD03_M03_34_HPP