// See https://www.interviewcake.com/question/cpp/cake-thief?course=fc1&section=dynamic-programming-recursion

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

struct cake {
	cake(uint32_t weight, uint32_t value)
		: weight{weight}
		, value{value}
	{}

	uint32_t weight, value;
};

uint32_t get_max_value(const std::vector<cake>& cakes, int capacity)
{
	std::vector<uint32_t> best_vals(capacity + 1);

	// Weird edge case - we can have as many zero weight cakes as we like so
	// we can always return the maximum possible value.
	for (const cake& cake : cakes) {
		if (cake.weight == 0 && cake.value > 0)
			return std::numeric_limits<decltype(cake.weight)>::max();
	}

	for (int i = 0; i <= capacity; i++) {
		uint32_t val = std::numeric_limits<uint32_t>::min();
		for (const cake& cake : cakes) {
			if (i < cake.weight)
				continue;

			val = std::max(val, best_vals[i - cake.weight] + cake.value);
		}
		best_vals[i] = val;
	}

	return best_vals[capacity];
}

int main()
{
	std::vector<cake> cakes = {
		cake(7, 160),
		cake(3, 90),
		cake(2, 15),
	};

	std::cout << get_max_value(cakes, 0) << std::endl;
	std::cout << "---" << std::endl;

	for (int i = 0; i <= 20; i++) {
		std::cout << get_max_value(cakes, i) << std::endl;
	}

	std::cout << "---" << std::endl;
	cakes.push_back(cake(0, 0));
	std::cout << get_max_value(cakes, 20) << std::endl;
	std::cout << "---" << std::endl;
	cakes.push_back(cake(0, 1));
	std::cout << get_max_value(cakes, 20) << std::endl;

	return 0;
}
