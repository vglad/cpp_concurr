// Module 5: C++ memory model and atomic operations
// 42. Functionality of std::atomic_bool

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD05_M05_42_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD05_M05_42_HPP

#include <iostream>
#include <atomic>

namespace concurr::m05_42 {

void run() {
  auto flag1 = std::atomic<bool> {};
  std::cout << "flag1 = " << flag1 << "\n";

  //not CopyConstructible
  //std::atomic<bool> flag2(flag1);

  //not CopyAssignable
  //std::atomic<bool> flag3 = flag1;

  //can construct using non atomic boolean value
  auto non_atomic_bool = true;
  auto flag4(std::atomic<bool> { non_atomic_bool });
  std::cout << "flag4 = " << flag4 << "\n";

  //can assign non atomic boolean value
  auto flag5 = std::atomic<bool> { non_atomic_bool };
  std::cout << "flag5 = " << flag5 << "\n";


  auto x = std::atomic<bool> { false };
  std::cout << "atomic boolean is implemented lock free: "
            << (x.is_lock_free() ? "yes" : "no") << "\n";

  //store and load operations
  auto y = std::atomic<bool> { true };
  x.store(false);
  std::cout << "value of atomic bool after store with non atomic type: " 
            << x.load() << "\n";
  x.store(y);
  std::cout << "value of atomic bool after store with another atomic type: " 
            << x.load() << "\n";

  //exchange operations
  auto z = x.exchange(false);
  std::cout << "value of previous atomic bool before exchange is: " << z << "\n";
  std::cout << "value of current atomic bool after exchange is: " << x.load() << "\n";
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD05_M05_42_HPP