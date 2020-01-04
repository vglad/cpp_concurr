// Module 3: Communication between threads using condition variables and futures
// 25. Introduction to condition variables

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD03_M03_25_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD03_M03_25_HPP

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

namespace concurr::m03_25 {

using namespace std::chrono_literals;

auto const distance_to_destination = int8_t { 10 };
auto distance_covered = int8_t { 0 };

bool keep_driving() {
  while (distance_covered < 15) {
    std::this_thread::sleep_for(1s);
    ++distance_covered;
  }
  return false;
}

void keep_awake_all_night() {
  for (; distance_covered < distance_to_destination;) {
    std::cout << "Keep check, whether i am there\n";
    std::this_thread::sleep_for(1s);
  }
  std::cout << "Arrived, distance_covered = " 
    << std::to_string(distance_covered) << "\n";
}

void set_the_alarm_and_take_a_nap() {
  if (distance_covered < distance_to_destination) {
    std::cout << "Let me take a nap\n";
    std::this_thread::sleep_for(10s);
  }
  std::cout << "Arrived, distance_covered = " 
    << std::to_string(distance_covered) << "\n";
}

void run() {
  auto driver_thread               = std::thread(keep_driving);
  auto keep_awake_all_night_thread = std::thread(keep_awake_all_night);
  auto set_the_alarm_thread        = std::thread(set_the_alarm_and_take_a_nap);

  driver_thread.join();
  keep_awake_all_night_thread.join();
  set_the_alarm_thread.join();
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD03_M03_25_HPP