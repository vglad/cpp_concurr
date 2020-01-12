// Module 3: Communication between threads using condition variables and futures
// 32. Introduction to package_task

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD03_M03_32_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD03_M03_32_HPP

#include <iostream>
#include <future>
#include <thread>

namespace concurr::m03_32 {

using namespace std::chrono_literals;

int add(int x, int y) {
  std::this_thread::sleep_for(500ms);
  std::cout << "add function runs in: " << std::this_thread::get_id() << "\n";
  return x + y;
}

void task_thread() {
  auto task_1 = std::packaged_task<int(int, int)>(add);
  auto future_1 = task_1.get_future();

  auto thread_1 = std::thread(std::move(task_1), 5, 6);
  thread_1.detach();
  std::cout << "task thread - " << future_1.get() << "\n";
}

void task_normal() {
  auto task_1   = std::packaged_task<int(int, int)>(add);
  auto future_1 = task_1.get_future();
  task_1(7, 8);
  std::cout << "task normal - " << future_1.get() << "\n";
}

void run() {
  task_thread();
  task_normal();
  std::cout << "main thread id :" << std::this_thread::get_id() << "\n";
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD03_M03_32_HPP