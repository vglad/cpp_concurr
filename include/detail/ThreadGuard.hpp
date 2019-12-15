#ifndef CPP_CONCURR_INCLUDE_DETAIL_THREADGUARD_HPP
#define CPP_CONCURR_INCLUDE_DETAIL_THREADGUARD_HPP

#include <vector>
#include <thread>

namespace detail {

class thread_guard {
public:
  explicit thread_guard(std::thread& t_) : t(t_) {
  }
  ~thread_guard() {
    if (t.joinable())
      t.join();
  }

  thread_guard(thread_guard const&) = delete;
  thread_guard& operator=(thread_guard const&) = delete;

private:
  std::thread& t;
};

}

#endif //CPP_CONCURR_INCLUDE_DETAIL_THREADGUARD_HPP