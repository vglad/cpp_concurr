// Module 4: Lock based thread safe data structures and algorithm implementation
// 38. thread safe queue implementation as linked list

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD04_M04_38_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD04_M04_38_HPP

#include <iostream>
#include <thread>
#include <condition_variable>

namespace concurr::m04_38 {

using namespace std::chrono_literals;

template<typename T>
class sequential_queue {
	struct node {
		std::shared_ptr<T>		data = nullptr;
		std::unique_ptr<node> next = nullptr;

		node() {}
		node(T data_) : data { std::move(data_) } {}
	};

	std::mutex							head_mutex = {};
	std::mutex							tail_mutex = {};
	std::condition_variable cv = {};

	std::unique_ptr<node>		head = nullptr;
	node*										tail = nullptr;

	node* get_tail() {
		auto tlg = std::lock_guard<std::mutex>(tail_mutex);
		return tail;
	}

	std::unique_ptr<node> wait_pop_head() {
		auto ul = std::unique_lock<std::mutex>(head_mutex);
		cv.wait(ul, [&] {	return head.get() != get_tail(); });
		auto old_head = std::move(head);
		head = std::move(old_head->next);
		return old_head;
	}

public:
	sequential_queue() : head { std::make_unique<node>() }, tail { head.get() } {}
	 
	void push(T value) {
		auto const new_data_p = std::make_shared<T>(std::move(value));
		auto new_dummy_node = std::make_unique<node>();
		auto const new_tail = new_dummy_node.get();

		{
			auto tlg = std::lock_guard<std::mutex>(tail_mutex);
			tail->data = new_data_p;
			tail->next = std::move(new_dummy_node);
			tail = new_tail;
		}

		cv.notify_one();
	}

	std::shared_ptr<T> pop() {
		auto hlg = std::lock_guard<std::mutex>(head_mutex);
		if (head.get() == get_tail()) {
			return {};
		}
		auto const top_data = head->data;
		auto const old_head = std::move(head);
		head = std::move(old_head->next);
		return top_data;
	}

	std::shared_ptr<T> wait_pop() {
		auto old_head = wait_pop_head();
		return old_head ? old_head->data : std::shared_ptr<T>{};
	}

};

void run() {
	sequential_queue<int> queue;
	//queue.push(3);
	//queue.push(4);
	//queue.push(7);
	//queue.push(5);
	//queue.pop();
	
	auto thread_1 = std::thread(&sequential_queue<int>::push, &queue, 1);
	auto thread_2 = std::thread(&sequential_queue<int>::push, &queue, 2);
	auto pop_1 = queue.wait_pop();
	auto thread_3 = std::thread(&sequential_queue<int>::push, &queue, 3);
	


	thread_1.join();
	thread_2.join();
	thread_3.join();
	
	if (pop_1 != nullptr) {
		std::cout << *pop_1 << "\n";
	} else {
		std::cout << "pop_1 is nullptr\n";
	}
	
}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD04_M04_38_HPP