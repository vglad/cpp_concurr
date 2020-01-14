// Module 6: Lock free data structures and algorithms
// 59. Simple lock free thread safe stack (reference, with memory leak)

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD06_M06_59_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD06_M06_59_HPP

#include <atomic>
#include <memory>

namespace concurr::m06_59 {

template<typename T>
class lock_free_stack {
public:

	void push(T const& data_) {
		node* const new_node = new node(data_);
		new_node->next = head.load();
		while (!head.compare_exchange_weak(new_node->next, new_node)) {
		}
	}

	std::shared_ptr<T> pop(T& result) {
		node* old_head = head.load();
		while (old_head && !head.compare_exchange_weak(old_head, old_head->next)) {
		}
		return old_head ? old_head.data : std::shared_ptr<T>();
	}


private:
	struct node {
		node(T const& data_) : data(std::make_shared<T>(data_)) {
		}

		std::shared_ptr<T> data;
		node* next;
	};

	std::atomic<node*> head;
};

void run() {

}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD06_M06_59_HPP