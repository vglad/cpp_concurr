// Module 3: Communication between threads using condition variables and futures
// 33. Communication between threads using std::promises

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD03_M03_33_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD03_M03_33_HPP

#include <iostream>
#include <future>
#include <thread>

namespace concurr::m03_33 {

using namespace std::chrono_literals;

void print_int(std::future<int>& fut) {
  std::cout << "waiting for value from print thread\n";
  
  //this thread will wait until promise set in other thread
  auto const value = fut.get();

  std::cout << "value: " << value << "\n";
  
}

void run() {
  auto prom = std::promise<int>();
  auto fut = prom.get_future();
  
  auto print_thread = std::thread(print_int, std::ref(fut));

  std::this_thread::sleep_for(3s);
  std::cout << "settint the value in the main thread\n";
  prom.set_value(10);

  print_thread.join();
  
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD03_M03_33_HPP