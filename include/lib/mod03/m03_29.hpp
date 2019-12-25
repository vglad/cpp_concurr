#ifndef CPP_CONCURR_INCLUDE_LIB_MOD03_M03_29_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD03_M03_29_HPP

#include <iostream>
#include <string>
#include <future>

namespace concurr::m03_29 {

int64_t find_answer_how_old_the_universe_is() {
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