// Module 5: C++ memory model and atomic operations
// 56. Implementation of spin lock mutex

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD05_M05_56_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD05_M05_56_HPP

#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>

namespace concurr::m05_56 {

using namespace std::chrono_literals;

class spinlock_mutex {
public:
	spinlock_mutex() {};

	void lock() {
		while (flag.test_and_set(std::memory_order_acquire));
	}

	void unlock() {
		flag.clear(std::memory_order_release);
	}

private:
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
};

auto mutex = spinlock_mutex {};

void func() {
	auto lg = std::lock_guard<spinlock_mutex>(mutex);
	std::cout << std::this_thread::get_id() << "hello\n";
	std::this_thread::sleep_for(3s);
}

void run() {
	auto thr1 = std::thread(func);
	auto thr2 = std::thread(func);
	thr1.join();
	thr2.join();

}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD05_M05_56_HPP