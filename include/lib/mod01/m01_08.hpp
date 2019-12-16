#ifndef CPP_CONCURR_INCLUDE_LIB_MOD01_M01_08_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD01_M01_08_HPP

#include <thread>
#include <chrono>
#include <string>
#include <iostream>

namespace concurr::m01_08 {

using namespace std::chrono_literals;

void c_clean() {
  std::cout << "Cleaning crew working...\n";
  std::this_thread::sleep_for(2s);
  std::cout << "Cleaning finished\n";
}

void c_full_speed() {
  std::cout << "Engine crew working.\nGoing full speed...\n";
  std::this_thread::sleep_for(2s);
  std::cout << "Full speed achieved\n";
}

void c_stop() {
  std::cout << "Engine crew working.\nStopping...\n";
  std::this_thread::sleep_for(2s);
  std::cout << "Ship stopped\n";
}

void run() {
  std::cout << "Enter command:\n";
  for (auto command = std::string {};;) {
    switch (std::cin >> command; std::stoi(command)) {
      case 1: {
        auto t_clean = std::thread(c_clean);
        t_clean.detach();
        break;
      }
      case 2: {
        auto t_full_speed = std::thread(c_full_speed);
        t_full_speed.join();
        break;
      }
      case 3: {
        auto t_stop = std::thread(c_stop);
        t_stop.join();
        break;
      }
      case 100: {
        return;
      }
      default: {
        std::cout << "Unknown command\n";
        break;
      }
    }
  }
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD01_M01_08_HPP