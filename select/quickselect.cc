#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

int partition(std::vector<int>& ns, int start, int end, int pivot_index)
{
	int pivot = ns[pivot_index];
	// Place pivot at end of array.
	std::swap(ns[pivot_index], ns[end]);

	int new_pivot_index = start;
	for (int i = start; i < end; i++) {
		if (ns[i] <= pivot) {
			std::swap(ns[i], ns[new_pivot_index++]);
		}
	}

	// Place back into place.
	std::swap(ns[end], ns[new_pivot_index]);

	return new_pivot_index;
}

int choose_random(int from, int to)
{
	// We assume from < to.
	return from + rand() % (to - from + 1);
}

int quick_select(std::vector<int>& ns, int k)
{
	int start = 0;
	int end = ns.size() - 1;
	while (start <= end) {
		const int pivot_index = choose_random(start, end);
		const int index = partition(ns, start, end, pivot_index);
		if (index + 1 == k)
			return ns[index];
		if (k < index + 1) {
			end = index - 1;
		} else {
			start = index + 1;
		}
	}

	return -1;
}

int main()
{
	std::vector<int> ns = { 3, 1, 7, 2 };

	std::cout << quick_select(ns, 4) << std::endl;

	return 0;
}
