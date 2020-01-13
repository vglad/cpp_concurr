// Module 5: C++ memory model and atomic operations
// 41. Functionality of std::atomic_flag

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD05_M05_41_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD05_M05_41_HPP

#include <iostream>
#include <atomic>

namespace concurr::m05_41 {

void run() {
  auto flag = std::atomic_flag { ATOMIC_FLAG_INIT };

  //set the flag to true and return previous value
  std::cout << "1. Previous flag value: " << flag.test_and_set() << "\n";
  std::cout << "2. Previous flag value: " << flag.test_and_set() << "\n";

  //clear the flag value
  flag.clear();
  
  std::cout << "3. Previous flag value: " << flag.test_and_set() << "\n";

}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD05_M05_41_HPP