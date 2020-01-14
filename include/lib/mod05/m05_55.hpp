// Module 5: C++ memory model and atomic operations
// 55. Concept of release sequence

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD05_M05_55_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD05_M05_55_HPP

#include <iostream>
#include <atomic>
#include <thread>
#include <queue>

namespace concurr::m05_55 {

using namespace std::chrono_literals;

auto count      = std::atomic<int> { 0 };
auto data_queue = std::queue<int> {};
auto max_count  = int { 20 };

void writer_queue() {
	for (auto i = 0; i < 20; ++i) {
		data_queue.push(i);
	}
	count.store(20, std::memory_order_release);
}

void reader_queue() {
	while (true) {
		auto item_index = int { 0 };
		if ((item_index = count.fetch_sub(1, std::memory_order_acquire)) > 0) {
			//wait for items
			std::this_thread::sleep_for(200ms);
			continue;
		}
		//process the item
		break;
	}
}

void run() {
	auto writer_thread  = std::thread(writer_queue);
	auto reader_thread1 = std::thread(reader_queue);
	auto reader_thread2 = std::thread(reader_queue);

	writer_thread.join();
	reader_thread1.join();
	reader_thread2.join();
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD05_M05_55_HPP