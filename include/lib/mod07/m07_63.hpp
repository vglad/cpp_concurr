// Module 7: Thread pools
// 63. 

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD07_M07_63_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD07_M07_63_HPP

#include <atomic>
#include <memory>
#include <thread>
#include <functional>
#include <vector>

namespace concurr::m07_63 {

//using namespace concurr::m03_28;

class join_threads {
public:
	explicit join_threads(std::vector<std::thread>& _threads) :
		threads(_threads) {
	}

	~join_threads() {
		for (size_t i = 0; i < threads.size(); i++) {
			if (threads[i].joinable())
				threads[i].join();
		}
	}

private:
	std::vector<std::thread>& threads;
};

class thread_pool {
public:
	thread_pool() : joiner(threads) {
		int const thread_count = std::thread::hardware_concurrency();
		try {
			for (auto i = 0; i < thread_count; i++) {
				threads.push_back(std::thread(&thread_pool::worker_thread, this));
			}
		} catch (...) {
				done.store(true);
				throw;
		}
	}

	~thread_pool() {
		done.store(true);
	}

	template<typename Function_type>
	void submit(Function_type f) {
		work_queue.push(std::function<void()>(f));
	}

private:
	std::atomic_bool done = { false };
	concurr::m03_28::thread_safe_queue<std::function<void()>> work_queue = {};
	std::vector<std::thread> threads = {};
	join_threads joiner;

	void worker_thread() {
		std::cout << "test";
		while (!done) {
			std::function<void()> task;
			if (work_queue.pop(task)) {
				task();
			} else {
				std::this_thread::yield();
			}
		}
	}
};


void run() {
	auto pool = thread_pool {};
	std::cout << "Testing thread pool:\n";

	for (auto i = 0; i < 100; i++) {
		pool.submit([=] {
			std::cout << i << " printed by thread: " << std::this_thread::get_id() << "\n";
		});
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}


}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD07_M07_63_HPP