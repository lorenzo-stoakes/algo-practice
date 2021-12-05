// See https://www.interviewcake.com/question/cpp/highest-product-of-3?course=fc1&section=greedy

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

int product3(const std::vector<int>& ns)
{
	if (ns.size() < 3)
		throw std::runtime_error("<3 input");

	int smallest = std::min(ns[0], ns[1]);
	int smallest2 = std::max(ns[0], ns[1]);
	int largest = smallest2;
	int largest2 = smallest;

	int best = ns[0] * ns[1] * ns[2];
	for (size_t i = 2; i < ns.size(); i++) {
		const int num = ns[i];

		best = std::max(best, num * largest * largest2);
		best = std::max(best, num * smallest * smallest2);
		best = std::max(best, num * smallest * largest);

		if (num < smallest) {
			smallest2 = smallest;
			smallest = num;
		} else if (num < smallest2) {
			smallest2 = num;
		}

		if (num > largest) {
			largest2 = largest;
			largest = num;
		} else if (num > largest2) {
			largest2 = num;
		}
	}

	return best;
}

int main()
{
	std::cout << product3({ -1, 0, 1, -1}) << std::endl;
	std::cout << product3({ -10, -10, 1, 3, 2}) << std::endl;
	std::cout << product3({ -10, 1, 3, 2, -10}) << std::endl;

	return 0;
}
