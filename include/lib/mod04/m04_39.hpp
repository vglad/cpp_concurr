// Module 4: Lock based thread safe data structures and algorithm implementation
// 39. parallel quick sort algorithm implementation

#ifndef CPP_CONCURR_INCLUDE_LIB_MOD04_M04_39_HPP
#define CPP_CONCURR_INCLUDE_LIB_MOD04_M04_39_HPP

#include <iostream>
#include <algorithm>
#include <list>
#include <future>

namespace concurr::m04_39 {

using namespace std::chrono_literals;

template<typename T>
std::list<T> sequential_quick_sort(std::list<T> input) {
	//recutsive condition
	if (input.size() < 2) {
		return input;
	}

	// move first element int the list to result list and take it as pivot value
	auto result = std::list<T> {};
	result.splice(std::begin(result), input, std::begin(input));
	auto pivot = *std::begin(result);

	// patition the input array so that t<pivot in lower part 
	// and t>pivot in upper part of input list
	auto divide_point = std::partition(std::begin(input), std::end(input),
																		 [&pivot](T const& t) { return t < pivot; }
	);

	//move lower part of the list to separate list so that we can make recursive call
	auto lower_list = std::list<T> {};
	lower_list.splice(std::end(lower_list), input, std::begin(input), divide_point);

	//call the sequential_quick_sort recursively
	auto new_lower = sequential_quick_sort(std::move(lower_list));
	auto new_upper = sequential_quick_sort(std::move(input));

	//transfer all elements into result list
	result.splice(std::begin(result), new_lower);
	result.splice(std::end(result), new_upper);

	return result;
}

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input) {
	//recutsive condition
	if (input.size() < 2) {
		return input;
	}

	// move first element int the list to result list and take it as pivot value
	auto result = std::list<T> {};
	result.splice(std::begin(result), input, std::begin(input));
	auto pivot = *std::begin(result);

	// patition the input array so that t<pivot in lower part 
	// and t>pivot in upper part of input list
	auto divide_point = std::partition(std::begin(input), std::end(input),
																		 [&pivot](T const& t) { return t < pivot; }
	);

	//move lower part of the list to separate list so that we can make recursive call
	auto lower_list = std::list<T> {};
	lower_list.splice(std::end(lower_list), input, std::begin(input), divide_point);

	//call the parallel_quick_sort recursively and asynchronously
	auto new_lower_future = std::future<std::list<T>>(
		std::async(&parallel_quick_sort<T>, std::move(lower_list))
		);
	auto new_upper_future = std::future<std::list<T>>(
			std::async(&parallel_quick_sort<T>, std::move(input))
	);

	//transfer all elements into result list
	result.splice(std::begin(result), new_lower_future.get());
	result.splice(std::end(result), new_upper_future.get());

	return result;
}

void run() {
	std::cout << "Sequential quick sort:\n";
	auto my_list_seq = std::list<int> { 8, 3, 12, 9, 5, 6, 11, 1, 13, 2, 11, 1, 13, 2 };
	auto result_seq = sequential_quick_sort<int>(my_list_seq);
	for each (int var in result_seq) {
		std::cout << var << std::endl;
	}
	std::cout << "\nParallel quick sort:\n";
	auto my_list_par = std::list<int> { 8, 3, 12, 9, 5, 6, 11, 1, 13, 2, 11, 1, 13, 2 };
	auto result_par = parallel_quick_sort<int>(my_list_par);
	for each (int var in result_par) {
		std::cout << var << std::endl;
	}

}

}

#endif //CPP_CONCURR_INCLUDE_LIB_MOD04_M04_39_HPP