// See https://www.interviewcake.com/question/cpp/product-of-other-numbers?course=fc1&section=greedy

// Product of all _other_ integers, can't divide.

#include <cstdint>
#include <iostream>
#include <vector>

std::vector<int64_t> other_prod(const std::vector<int64_t>& ns)
{
	std::vector<int64_t> ret(ns.size(), 1);

	// Forwards
	int64_t prod = 1;
	for (size_t i = 1; i < ns.size(); i++) {
		int64_t n = ns[i - 1];
		prod *= n;
		ret[i] = prod;
	}

	// Backwards
	prod = 1;
	for (ssize_t i = ns.size() - 2; i >= 0; i--) {
		int64_t n = ns[i + 1];
		prod *= n;
		ret[i] *= prod;
	}

	return ret;
}

int main()
{
	for (const int n : other_prod({ 0, 1, 7, 3, 4})) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	return 0;
}
