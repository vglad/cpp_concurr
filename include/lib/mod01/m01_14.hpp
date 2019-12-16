#ifndef CPP_CONCURR_INCLUDE_LIB_MOD01_M01_14_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD01_M01_14_HPP

#include <thread>
#include <vector>
#include <numeric>
#include <iostream>
#include <string>

namespace concurr::m01_14 {

void sequential_accum_test() {
  auto v         = std::vector<int> { 1,2,3,4,5,6,7,8,9,10 };
  auto dash_fold = [](std::string a, int b) {
                        return std::move(a) + "-" + std::to_string(b);
  };

  auto sum     = std::accumulate(std::begin(v), std::end(v), 0);
  auto product = std::accumulate(std::begin(v), std::end(v), 
                                 1,
                                 std::multiplies<int>());
  auto str     = std::accumulate(std::next(std::begin(v)), std::end(v),
                                 std::to_string(v[0]),
                                 dash_fold);

  std::cout << "sum - " << sum << "\n";
  std::cout << "product - " << product << "\n";
  std::cout << "dash fold - " << str << "\n";
}

void run() {
  sequential_accum_test();
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD01_M01_14_HPP