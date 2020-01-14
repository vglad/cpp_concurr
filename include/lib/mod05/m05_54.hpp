// Module 5: C++ memory model and atomic operations
// 54. Discussion on memory_order_consume

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD05_M05_54_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD05_M05_54_HPP

#include <iostream>
#include <atomic>
#include <thread>
#include <cassert>

namespace concurr::m05_54 {

struct X {
	int i = 0;
	std::string s = "";
};

std::atomic<X*> p = nullptr;
auto a = std::atomic<int> { 0 };

void create_x() {
	X* x = new X;
	x->i = 42;
	x->s = "hello";

	a.store(20, std::memory_order_relaxed);
	p.store(x, std::memory_order_release);
}

void use_x() {
	X* x;
	while ((x = p.load(std::memory_order_consume)) == nullptr) {};
	assert(x->i == 42);
	assert(x->s == "hello");
	assert(a.load(std::memory_order_relaxed) == 20);
	std::cout << "x->i = " << x->i << "\nx->s = " << x->s << "\n";
}

void run() {
	auto create_thread = std::thread(create_x);
	auto use_thread		 = std::thread(use_x);

	create_thread.join();
	use_thread.join();
  
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD05_M05_54_HPP