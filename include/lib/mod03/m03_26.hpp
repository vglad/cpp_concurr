// Module 3: Communication between threads using condition variables and futures
// 26. Details about condition variables

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD03_M03_26_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD03_M03_26_HPP

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <condition_variable>
#include <mutex>

namespace concurr::m03_26 {

using namespace std::chrono_literals;

auto have_i_arrived       = false;
auto const total_distance = int8_t { 10 };
auto distance_covered     = int8_t { 0 };
auto cv                   = std::condition_variable {};
auto m                    = std::mutex {};

void keep_moving() {
  for (;;) {
    std::this_thread::sleep_for(1s);
    ++distance_covered;

    //notify the waiting threads if the event occurs
    if (distance_covered == total_distance) {
      cv.notify_one();
    }
    std::cout << "Keep moving...\n";
  }
}

void ask_driver_to_wake_you_up_at_right_time() {
  auto ul = std::unique_lock<std::mutex>(m);
  cv.wait(ul, [] { return distance_covered == total_distance; });
  std::cout << "Arrived, distance_covered = " 
    << std::to_string(distance_covered) << "\n";
}

void run() {
  auto driver_thread    = std::thread(keep_moving);
  auto passenger_thread = std::thread(ask_driver_to_wake_you_up_at_right_time);

  passenger_thread.join();
  driver_thread.join();
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD03_M03_26_HPP