// Module 3: Communication between threads using condition variables and futures
// 34. std::shared_futures

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD03_M03_35_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD03_M03_35_HPP

#include <iostream>
#include <future>
#include <thread>

namespace concurr::m03_35 {

using namespace std::chrono_literals;

//can not use single future in simultaneous access
//void print_result(std::future<int>& fut) {
//  //future expires after first call
//  std::cout << fut.get() << "\n";
//
//  //race condition in that case
//  if (fut.valid()) {
//    std::cout << "this is valid future\n" << fut.get() << "\n";
//  } else {
//    std::cout << "this is invalid future\n";
//  }
//}

void print_result(std::shared_future<int>& fut) {
  std::cout << fut.get() << " - valid future\n";
}

void run() {
  auto prom = std::promise<int>();
  
  //usage of single future throw exception
  //auto fut = prom.get_future();
  
  //we need to use shared_future in case of simultaneous access
  auto fut  = std::shared_future<int>(prom.get_future());

  auto th1 = std::thread(print_result, std::ref(fut));
  auto th2 = std::thread(print_result, std::ref(fut));

  prom.set_value(5);
  th1.join();
  th2.join();
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD03_M03_35_HPP