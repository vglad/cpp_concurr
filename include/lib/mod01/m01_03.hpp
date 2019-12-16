#ifndef CPP_CONCURR_INCLUDE_LIB_MOD01_M01_03_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD01_M01_03_HPP

#include <iostream>
#include <thread>

namespace concurr {
namespace m01_03 {

class callable_class {
public:
  auto operator()() {
    std::cout << "Hello from callable class - "
      << std::this_thread::get_id() << "\n";
  }
};

void foo() {
  std::cout << "Hello from foo - " << std::this_thread::get_id() << "\n";
}

void run() {
  auto obj = callable_class {};
  auto thread1 = std::thread(foo);
  auto thread2 = std::thread(obj);
  auto thread3 = std::thread([] {std::cout << "Hello from lambda - "
                             << std::this_thread::get_id()
                             << "\n"; }
  );

  thread1.join();
  thread2.join();
  thread3.join();

  std::cout << "Hello from run - " << std::this_thread::get_id() << "\n";
}

}
}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD01_M01_03_HPP