#ifndef CPP_CONCURR_INCLUDE_LIB_MOD01_M01_13_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD01_M01_13_HPP

#include <thread>
#include <chrono>
#include <queue>
#include <iostream>
#include <string>

//2 std::queue type vars - engine and clean work queue

//engine and cleaning crew represented by one thread each

//threads should be run iteratively to check for done flag
//which is 100 (intup from console)

//each iteration each thread checked for available commands in
//corresponding queue
//you can put command from the main queue (console)

//if any command found, execute it and sleep for 1sec
//if empty queue, sleep for 2sec

//captain should not wait for command completion to accept next command
//1sec interval between commands

namespace concurr::m01_13 {

using namespace std::chrono_literals;

void clean_worker(std::queue<int>& q) {
  for (;;) {
    switch (auto c = [&] {return !q.empty() ? q.front() : 0; } (); c) {
      case 1: {
        q.pop();
        std::cout << "Cleaning crew working...\n";
        std::this_thread::sleep_for(1s);
        std::cout << "Cleaning finished\n";
        break;
      }
      case 100: {
        std::cout << "Closing cleaning crew queue...\n";
        return;
      }
      default: {
        std::cout << "No commands in cleaning queue\n";
        std::this_thread::sleep_for(2s);
      }
    }
  }
}

void engine_worker(std::queue<int>& q) {
  for (;;) {
    switch (auto c = [&] {return !q.empty() ? q.front() : 0; } (); c) {
      case 2: {
        q.pop();
        std::cout << "Engine crew working. Going full speed...\n";
        std::this_thread::sleep_for(1s);
        std::cout << "Full speed achieved\n";
        break;
      }
      case 3: {
        q.pop();
        std::cout << "Engine crew working. Stopping...\n";
        std::this_thread::sleep_for(1s);
        std::cout << "Ship stopped\n";
        break;
      }
      case 100: {
        std::cout << "Closing engine crew queue...\n";
        return;
      }
      default: {
        std::cout << "No commands in engine queue\n";
        std::this_thread::sleep_for(2s);
      }
    }
  }
}

int check_command(std::string const& command) {
  try {
    return std::stoi(command);
  } catch (...) {
    return 0;
  }
}

void run() {
  auto q_clean = std::queue<int> {};
  auto t_clean = std::thread(clean_worker, std::ref(q_clean));

  auto q_engine = std::queue<int> {};
  auto t_engine = std::thread(engine_worker, std::ref(q_engine));

  std::cout << "Enter command:\n";
  for (auto command = std::string {};;) {
    std::cin >> command;
    switch (auto const c = check_command(command); c) {
      case 1: {
        q_clean.push(c);
        break;
      }
      case 2:
      case 3: {
        q_engine.push(c);
        break;
      }
      case 100: {
        std::cout << "Closing all queues...\n";
        q_clean.push(c);
        q_engine.push(c);
        t_clean.join();
        t_engine.join();
        std::cout << "Done\n";
        return;
      }
      default: {
        std::cout << "Unknown command - " << command << "\n";
      }
    }
    std::this_thread::sleep_for(1s);
  }
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD01_M01_13_HPP