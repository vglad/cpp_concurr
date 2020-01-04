// Module 2: Thread safe access to shared data and locking mechanisms
// 19. Things to remember when using mutexes

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD02_M02_19_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD02_M02_19_HPP

#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <functional>

namespace concurr::m02_19 {

class list_wrapper {
public:
  void add_to_list(int x) {
    auto lg = std::lock_guard<std::mutex>(m);
    my_list.emplace_back(x);
  }

  //returned pointer can be used anywhere
  //pointer is not thead safe
  std::list<int>* get_data() {
    return &my_list;
  }

private:
  std::list<int> my_list;
  std::mutex m;

};

class data_object {
public:
  void some_operation() {
    std::cout << "Can change data...\n";
  }
};

class data_wrapper {
public:
  template <typename function>
  void do_some_work(function f) {
    auto lg = std::lock_guard<std::mutex>(m);
    f(protected_data);
  }

private:
  data_object protected_data;
  std::mutex m;
};

data_object* unprotected_data;
void malisious_function(data_object& data) {
  unprotected_data = &data;
}

void run() {
  auto wrapper = data_wrapper {};
  wrapper.do_some_work(malisious_function);
  unprotected_data->some_operation();
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD02_M02_19_HPP