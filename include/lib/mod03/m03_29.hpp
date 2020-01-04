// Module 3: Communication between threads using condition variables and futures
// 29. Introduction to futures and async tasks

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD03_M03_29_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD03_M03_29_HPP

#include <iostream>
#include <string>
#include <future>
#include <chrono>

namespace concurr::m03_29 {

using namespace std::chrono_literals;

int64_t find_answer_how_old_the_universe_is() {
  std::this_thread::sleep_for(3s);
  return 13'000'000'000;
}

void do_other_calculations() {
  std::cout << "Doing calculations...\n";
}

void run() {
  //std::future<int64_t> the_answer_future =
  //  std::async(find_answer_how_old_the_universe_is);
  auto the_answer_future = std::async(find_answer_how_old_the_universe_is);
  do_other_calculations();
  std::cout << "The answer is " 
    << std::to_string(the_answer_future.get()) << "\n";
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD03_M03_29_HPP