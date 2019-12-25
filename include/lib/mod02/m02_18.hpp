#ifndef CPP_CONCURR_INCLUDE_LIB_MOD02_M02_18_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD02_M02_18_HPP

#include <iostream>
#include <thread>
#include <list>
#include <mutex>

namespace concurr::m02_18 {

auto my_list = std::list<int> {};
auto m       = std::mutex {};

void add_to_list_with_raw_mutex(int x) {
  m.lock();
  my_list.emplace_back(x);
  m.unlock();
}

void add_to_list_with_lock_guard(int x) {
  auto lg = std::lock_guard<std::mutex>(m);
  my_list.emplace_back(x);
}

void run() {
  auto thread1 = std::thread(add_to_list_with_raw_mutex, 1);
  auto thread2 = std::thread(add_to_list_with_raw_mutex, 2);

  auto thread3 = std::thread(add_to_list_with_lock_guard, 3);
  auto thread4 = std::thread(add_to_list_with_lock_guard, 4);

  thread1.join();
  thread2.join();
  thread3.join();
  thread4.join();

  for (auto const& e : my_list) {
    std::cout << e << " ";
  }
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD02_M02_18_HPP