// Module 1: Thread management guide
// 15. Parallel accumulate algorithm implementation

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD01_M01_15_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD01_M01_15_HPP

#include <thread>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>

#include "Utils.hpp"

namespace concurr::m01_15 {

template<typename Iter, typename T>
void accumulate_block(Iter start, Iter end, T& result) {
  result = std::accumulate(start, end, 0);
}

template<typename Iter, typename T>
T accumulate_list(Iter start, Iter end, T init) {
  
  auto const elements_total = std::distance(start, end);
  if (elements_total <= 0) return init;
  
  auto constexpr min_elements_for_thread = 1'000'000;
  auto const max_threads = 
    static_cast<int>(elements_total / min_elements_for_thread);
//  std::cout << "Max number of threads to avoid heavy overload: " 
//            << max_threads << "\n";

  auto const allowed_threads = static_cast<int>(
                                std::thread::hardware_concurrency() > 0 ?
                                std::thread::hardware_concurrency()     :
                                2);
//  std::cout << "Max number of threads to avoid oversubscription: "
//            << allowed_threads << "\n";

  auto const running_threads = static_cast<int>(std::min(allowed_threads, max_threads));
//  std::cout << "Runing threads: " << running_threads << "\n";

  auto results = std::vector<T>(running_threads);
  auto threads = std::vector<std::thread>(running_threads - 1);
  
  auto const block_size = (elements_total + 1) / running_threads;
  auto block_start = Iter {start};
  
  for (int i = 0; i < (running_threads - 1); ++i) {
    auto block_end = Iter { block_start };
    std::advance(block_end, block_size);
    threads[i] = std::thread(
      accumulate_block<Iter, T>, block_start, block_end, std::ref(results[i]));
    block_start = block_end;
  }
  accumulate_block<Iter, T>(block_start, end, results[running_threads - 1]);

  std::for_each(
    std::begin(threads), std::end(threads), [](std::thread& t){ t.join(); });

  return std::accumulate(std::begin(results), std::end(results), init);
}

void run() {
  auto v = std::vector<int>(400'000'000);
  std::iota(std::begin(v), std::end(v), 0);

  auto const time_start_par = detail::time_now();
  auto const par_sum = accumulate_list(std::begin(v), std::end(v), 0);
  auto const time_end_par = detail::time_elapsed(time_start_par);
  std::cout << "Parallel sum of list: " << par_sum << ". Elapsed: "
            << std::to_string(time_end_par) << "\n";


  auto const time_start_seq = detail::time_now();
  auto const seq_sum = std::accumulate(std::begin(v), std::end(v), 0);
  auto const time_end_seq = detail::time_elapsed(time_start_seq);
  std::cout << "Sequential sum of list: " << seq_sum << ". Elapsed: "
            << std::to_string(time_end_seq) << "\n";

}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD01_M01_15_HPP