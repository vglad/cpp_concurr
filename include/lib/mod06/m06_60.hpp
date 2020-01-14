// Module 6: Lock free data structures and algorithms
// 60. Stack memory reclaim mechanism using thread counting

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD06_M06_60_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD06_M06_60_HPP

#include <atomic>
#include <memory>

namespace concurr::m06_60 {

template<typename T>
class lock_free_stack_thr_counting {
public:
	lock_free_stack_thr_counting() {
	}

	void push(T const& data_) {
		node* const new_node = new node(data_);
		new_node->next = head.load();
		while (!head.compare_exchange_weak(new_node->next, new_node)) {
		}
	}

	std::shared_ptr<T> pop(T& result) {
		//increment the thread count in the pop function
		++threads_in_pop;

		node* old_head = head.load();
		while (old_head && !head.compare_exchange_weak(old_head, old_head->next)) {
		}
		
		//no need to have data in the node which is going to pass to try_reclaim
		auto res = std::make_shared<T>();
		if (old_head) {
			res.swap(old_head->data);
		}
		
		//node reclaim function call
		try_reclaim(old_head);
		return res;
	}

private:
	struct node {
		node(T const& data_) : data(std::make_shared<T>(data_)) {
		}

		std::shared_ptr<T> data;
		node* next;
	};

	std::atomic<node*> head;
	std::atomic<int> threads_in_pop;
	std::atomic<node*> to_be_deleted;

	void try_reclaim(node* old_head) {
		if (threads_in_pop == 1) {
			//delete node pointed by old_head
			delete old_head;
			node* claimed_list = to_be_deleted.exchange(nullptr);

			if (!--threads_in_pop) {
				delete_nodes(claimed_list);
			} else if (claimed_list) {
				node * last = claimed_list;
				while (node * const next = last->next) {
					last = next;
				}
				last->next = to_be_deleted;
				while (!to_be_deleted.compare_exchange_weak(last->next, claimed_list)) {
				}
			}

		} else {
			//add node pointed by old_head to to_be_deleted list
			old_head->next = to_be_deleted;
			while (!to_be_deleted.compare_exchange_weak(old_head->next, old_head)) {
			}
			--threads_in_pop;
		}
	}

	void delete_nodes(node* nodes) {
		while (nodes) {
			node* next = node->next;
			delete nodes;
			nodes = next;
		}
	}

};

void run() {

}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD06_M06_60_HPP