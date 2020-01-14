// Module 5: C++ memory model and atomic operations
// 44. atomic_pointers, fetch_add, fetch_sub, ++, --

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD05_M05_44_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD05_M05_44_HPP

#include <iostream>
#include <atomic>
#include <numeric>

namespace concurr::m05_44 {

void run() {
  int values1[20];
  std::iota(std::begin(values1), std::end(values1), 1);

  auto x1_ptr = std::atomic<int*> { values1 };
  std::cout << "is atomic int pointer lock free? - "
            << (x1_ptr.is_lock_free() ? "yes" : "no") << "\n";
  std::cout << "after initialisation atomic x1_ptr points to: " 
            << *x1_ptr << "\n";

  //we can change object atomic pointer points to
  auto y_ptr = values1 + 3;
  x1_ptr.store(y_ptr);
  std::cout << "value referencing to by atomic x1_ptr: " 
            << *(x1_ptr.load()) << "\n";
  
  //we can change object atomic pointer points to
  auto ret_value = x1_ptr.compare_exchange_weak(y_ptr, values1 + 10);
  std::cout << "store operation successful? - "
            << (ret_value ? "yes" : "no") << "\n";
  std::cout << "new value pointed to by atomic x1_ptr: "
            << *x1_ptr << "\n";

  
  int values2[20];
  std::iota(std::begin(values2), std::end(values2), 1);

  auto x2_ptr = std::atomic<int*> { values2 };
  std::cout << "after initialisation atomic x2_ptr points to: "
    << *x2_ptr << "\n";

  //fetch_add
  auto prev_x2_ptr_1 = x2_ptr.fetch_add(12);
  std::cout << "after fetch_add previous value pointed by x2_ptr: "
            << *prev_x2_ptr_1 << "\n";  
  std::cout << "after fetch_add new value pointed by x2_ptr: "
    << *x2_ptr << "\n";

  //fetch_sub
  auto prev_x2_ptr_2 = x2_ptr.fetch_sub(3);
  std::cout << "after fetch_sub previous value pointed by x2_ptr: "
    << *prev_x2_ptr_2 << "\n";
  std::cout << "after fetch_sub new value pointed by x2_ptr: "
    << *x2_ptr << "\n";

  //operator++
  x2_ptr++;
  std::cout << "after post increment new value pointed by x2_ptr: "
    << *x2_ptr << "\n";

  //operator--
  x2_ptr--;
  std::cout << "after post decrement new value pointed by x2_ptr: "
    << *x2_ptr << "\n";

}     

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD05_M05_44_HPP