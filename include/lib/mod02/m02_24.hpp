// Module 2: Thread safe access to shared data and locking mechanisms
// 24. Unique locks

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD02_M02_24_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD02_M02_24_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

namespace concurr::m02_24 {

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
    std::cout << "Lock both mutexes by " << thread_id << "\n";

    auto ul1 = std::unique_lock<std::mutex>(from.m, std::defer_lock);
    auto ul2 = std::unique_lock<std::mutex>(to.m, std::defer_lock);
    std::lock(ul1, ul2);

    from.balance -= amount;
    to.balance += amount;
    std::cout << "Transfer " << amount << " to " << to.name 
      << " from " << from.name << " in " << thread_id << " finished\n";

  }

private:
  double balance = 0.0;
  std::string name;
  std::mutex m;

};

void x_operation() {
  std::cout << "execute operation X\n";
}

void y_operation() {
  std::cout << "execute operation Y\n";
}

//will throw runtime error in VS2019 in x64-Debug or x64-Clang-Debug mode 
//warnings C26111 and C26115
std::unique_lock<std::mutex> get_lock() {
  auto m = std::mutex {};
  auto lk = std::unique_lock<std::mutex>(m);
  x_operation();
  return lk;
}

void run() {
  std::cout << "Using unique mutex lock example 1\n";
  auto account   = bank_account {};
  auto account_1 = bank_account(1000, "James");
  auto account_2 = bank_account(2000, "Mathew");

  auto thread_1 = std::thread(&bank_account::transfer, &account,
                              std::ref(account_1), std::ref(account_2), 100);
  std::this_thread::sleep_for(100ms);
  auto thread_2 = std::thread(&bank_account::transfer, &account,
                              std::ref(account_2), std::ref(account_1), 100);

  thread_1.join();
  thread_2.join();

  std::cout << "\nUsing unique mutex lock example 2\n";
  auto lk = std::unique_lock<std::mutex>(get_lock());
  y_operation();
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD02_M02_24_HPP