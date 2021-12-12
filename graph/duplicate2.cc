// See https://www.interviewcake.com/question/cpp/find-duplicate-optimize-for-space-beast-mode?course=fc1&section=trees-graphs
// See also search/duplicate.cc

#include <iostream>
#include <vector>

// Problem is - Integers in range 1..n in size n + 1 array.
// At least 1 duplicate - find any duplicate.

// TRICK: Treat the integers as a linked list which go to index - 1. If we do
// this, nodes with at least 2 inbound edges represent a duplication. This is
// also the beginning of a cycle. To find this:
//
// 1. Find an element in the cycle.
// 2. Use this to count the cycle length.
// 3. Use cycle length to find first element in cycle.

int advance(const std::vector<int>& ns, int index, int count)
{
	for (int i = 0; i < count; i++) {
		index = ns[index] - 1;
	}
	return index;
}

int advance(const std::vector<int>& ns, int index)
{
	return advance(ns, index, 1);
}

// Find an index within the cycle.
int find_cycle_index(const std::vector<int>& ns)
{
	// Use 2 indexes, 1 going faster than the other to detect the cycle.
	// We know last index must lead into the cycle since it cannot
	// self-cycle.

	int index1 = ns.size() - 1;
	int index2 = ns.size() - 1;

	index1 = advance(ns, index1);
	index2 = advance(ns, index2, 2);

	while (index1 != index2) {
		index1 = advance(ns, index1);
		index2 = advance(ns, index2, 2);
	}

	return index1;
}

// Count the cycle.
int count_cycle(const std::vector<int>& ns, int start_index)
{
	int count = 1;
	for (int index = ns[start_index] - 1; index != start_index;
	     index = ns[index] - 1) {
		count++;
	}

	return count;
}

// size == n + 1, containing 1..n.
// O(n) time, O(1) space
int find_duplicate(const std::vector<int>& ns)
{
	// First, find cycle length.
	int cycle_index = find_cycle_index(ns);
	// Now count the cycle.
	int cycle_count = count_cycle(ns, cycle_index);

	// Now simultaneously advance from last element and last element +
	// cycle_count steps forward until they match. When they match this will
	// be the first node in the cycle, the node with 2 inward edges.

	// This works because if we take x = distance to cycle and y = cycle
	// length, then we end up at `y - x` steps through the cycle for index2.
	// As we advance `x` steps, we will be `y` through the cycle, i.e. have
	// cycled again to the first element. Since index1 has stepped through
	// `x` times then index1 == index2 == index of first cycle == duplicate.

	int index1 = ns.size() - 1;
	int index2 = advance(ns, index1, cycle_count);

	while (index1 != index2) {
		index1 = advance(ns, index1);
		index2 = advance(ns, index2);
	}

	// Values in array are base-1.
	return index1 + 1;
}

int main()
{
	std::cout << find_duplicate({1, 2, 5, 5, 5, 5}) << std::endl;
	std::cout << find_duplicate({4, 1, 4, 8, 3, 2, 7, 6, 5}) << std::endl;
	std::cout << find_duplicate({3, 4, 2, 3, 1, 5}) << std::endl;

	return 0;
}
