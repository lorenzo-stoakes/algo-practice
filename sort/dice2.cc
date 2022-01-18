#include <array>
#include <cstddef>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

int solution(const std::vector<int>& a, const std::vector<int>& b)
{
	const size_t size_a = a.size();
	const size_t size_b = b.size();

	// It's just not possible in this case.
	if (size_a > 6 * size_b || size_b > 6 * size_a)
		return -1;

	int64_t sum_a = 0;
	for (const int n : a) {
		sum_a += n;
	}

	int64_t sum_b = 0;
	for (const int n : b) {
		sum_b += n;
	}

	const std::vector<int>& smaller = sum_a <= sum_b ? a : b;
	const std::vector<int>& bigger = sum_a > sum_b ? a : b;

	ssize_t delta = std::abs(sum_a - sum_b);

	// Calculate the maximum delta we can achieve with each die. Count sort.
	std::array<int, 7> delta_counts {};

	for (const int n : smaller) {
		// We can decrease delta by INCREASING smaller side dies.
		delta_counts[6 - n]++;
	}

	for (const int n : bigger) {
		// We can decrease delta by DECREASING larger side dies.
		delta_counts[n - 1]++;
	}

	// Now we simply work backwards through the maximum delta impacts we can
	// have, the count of this is the minimum number of die rotations.

	int turned = 0;

	for (int digit = 6; digit >= 1; digit--) {
		for (int count = 0; count < delta_counts[digit]; count++) {
			if (delta <= 0)
				goto done;

			delta -= digit;
			turned++;
		}
	}

  done:
	return turned;
}

int main()
{
	std::cout << solution({5}, { 1, 1, 6 }) << std::endl;
	std::cout << solution({2,3,1,1,2}, { 5, 4, 6 }) << std::endl;
	std::cout << solution({5,4,1,2,6,5}, { 2 }) << std::endl;
	std::cout << solution({1,2,3,4,3,2,1}, { 6 }) << std::endl;

	return 0;
}
