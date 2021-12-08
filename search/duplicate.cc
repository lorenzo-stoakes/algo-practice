// See https://www.interviewcake.com/question/cpp/find-duplicate-optimize-for-space?course=fc1&section=sorting-searching-logarithms

#include <iostream>
#include <stdexcept>
#include <vector>

// size == n + 1, containing 1..n.
int find_duplicate(const std::vector<int>& ns)
{
	// The maximum possible valid integer.
	int from = 1, to = ns.size() - 1;

	// Once from == to we're done.
	while (from < to) {
		int mid = (from + to) / 2;

		int first_count = 0;
		for (const int n : ns) {
			if (n >= from && n <= mid)
				first_count++;
		}

		// Exclusive range.
		int expected_first = mid - from + 1;

		// There can be FEWER in a range but that's ok, because of
		// duplicates in other half.
		if (first_count > expected_first)
			to = mid;
		else
			from = mid + 1;
	}

	if (from != to)
		throw std::runtime_error("argh!");

	return from;
}

int main()
{
	std::cout << find_duplicate({1, 2, 5, 5, 5, 5}) << std::endl;
	std::cout << find_duplicate({4, 1, 4, 8, 3, 2, 7, 6, 5}) << std::endl;

	return 0;
}
