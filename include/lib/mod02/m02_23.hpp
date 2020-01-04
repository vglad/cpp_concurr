// Module 2: Thread safe access to shared data and locking mechanisms
// 23. Dead locks

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD02_M02_23_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD02_M02_23_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

namespace concurr::m02_23 {

using namespace std::chrono_literals;

class bank_account {
public:
	bank_account() = default;

  bank_account(double balance_, std::string const& name_)
    : balance { balance_ }, name { name_ } {}

  bank_account(bank_account const&) = delete;
  bank_account& operator=(bank_account const&) = delete;

  void withdraw(double amount) {
    auto lg = std::lock_guard<std::mutex>(m);
    balance -= amount;
  }

  void deposit(double amount) {
    auto lg = std::lock_guard<std::mutex>(m);
    balance += amount;
  }

  void transfer(bank_account & from, bank_account & to, double amount) {
    auto thread_id = std::this_thread::get_id();
    auto lg_1 = std::lock_guard<std::mutex>(from.m);
    std::cout << "Lock for " << from.name << " account aquired by "
      << thread_id << "\n";
    std::this_thread::sleep_for(1s);

    std::cout << "Waiting to aquire lock for " << to.name << " account by "
      << thread_id << " ...\n";
    auto lg_2 = std::lock_guard<std::mutex>(to.m);

    from.balance -= amount;
    to.balance += amount;
    std::cout << "Transfer to " << to.name << " from " << from.name
      << "finished\n";

  }

private:
  double balance = 0.0;
  std::string name;
  std::mutex m;

};

auto m1 = std::mutex {};
auto m2 = std::mutex {};

void m1_first_m2_second() {
  auto thread_id = std::this_thread::get_id();
  std::cout << "Mutex aquired for m1 by " << thread_id << "\n";
  auto lg1 = std::lock_guard<std::mutex>(m1);
  std::this_thread::sleep_for(1s);
  std::cout << "Trying to aquire mutex for m2 by " << thread_id << " ...\n";
  auto lg2 = std::lock_guard<std::mutex>(m2);
  std::cout << "Mutex aquired\n";
}

void m2_first_m1_second() {
  auto thread_id = std::this_thread::get_id();
  std::cout << "Mutex aquired for m2 by " << thread_id << "\n";
  auto lg2 = std::lock_guard<std::mutex>(m2);
  std::this_thread::sleep_for(1.5s);
  std::cout << "Trying to aquire mutex for m1 by " << thread_id << " ...\n";
  auto lg1 = std::lock_guard<std::mutex>(m1);
  std::cout << "Mutex aquired\n";
}


void run() {
  std::cout << "Mutex lock example 1\n";
  auto account   = bank_account {};
  auto account_1 = bank_account(1000, "James");
  auto account_2 = bank_account(2000, "Mathew");

  auto thread_1 = std::thread(&bank_account::transfer, &account,
                              std::ref(account_1), std::ref(account_2), 100);
  std::this_thread::sleep_for(100ms);
  auto thread_2 = std::thread(&bank_account::transfer, &account,
                              std::ref(account_2), std::ref(account_1), 100);

  std::this_thread::sleep_for(2s);
  std::cout << "\nMutex lock example 2\n";
  
  auto thread_3 = std::thread(m1_first_m2_second);
  auto thread_4 = std::thread(m2_first_m1_second);

  thread_1.join();
  thread_2.join();
  thread_3.join();
  thread_4.join();
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD02_M02_23_HPP