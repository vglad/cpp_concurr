// Module 3: Communication between threads using condition variables and futures
// 31. Parallel accumulate algorithm implementation with async task

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD03_M03_31_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD03_M03_31_HPP

#include <iostream>
#include <string>
#include <future>
#include <numeric>

namespace concurr::m03_31 {

auto constexpr MIN_ELEMENT_COUNT = 1000;

template<typename iterator>
int parallel_accumulate(iterator begin, iterator end) {
  auto length = std::distance(begin, end);

  //at least runs 1000 elements
  if (length < MIN_ELEMENT_COUNT) {
    std::cout << std::this_thread::get_id() << "\n";
    return std::accumulate(begin, end, 0);
  }

  auto mid = begin;
  std::advance(mid, (length + 1) / 2);

  //recursive call to parallel_accumulate
  auto f1 = std::async(std::launch::deferred | std::launch::async,
                       parallel_accumulate<iterator>, mid, end);
  auto sum = parallel_accumulate(begin, mid);
  return sum + f1.get();
}

void run() {
  auto v = std::vector<int>(10000, 1);
  auto result = parallel_accumulate(std::begin(v), std::end(v));
  std::cout << "The sum is " << std::to_string(result) << "\n";
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD03_M03_31_HPP