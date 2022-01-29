#include <iostream>
#include <vector>

int bsearch(const std::vector<int>& ns, int sought)
{
	ssize_t start = 0;
	ssize_t end = ns.size();

	while (start < end) {
		const ssize_t middle = start + (end - start) / 2;
		const int middle_val = ns[middle];

		if (middle_val == sought)
			return middle;
		else if (middle_val < sought)
			start = middle + 1;
		else // middle_val > sought
			end = middle;
	}

	return -1;
}

int bsearch_leftmost(const std::vector<int>& ns, int sought)
{
	ssize_t start = 0;
	ssize_t end = ns.size();

	while (start < end) {
		const ssize_t middle = start + (end - start) / 2;
		const int middle_val = ns[middle];

		if (middle_val < sought)
			start = middle + 1;
		else // middle_val >= sought
			end = middle;
	}

	return start;
}

int bsearch_rightmost(const std::vector<int>& ns, int sought)
{
	ssize_t start = 0;
	ssize_t end = ns.size();

	while (start < end) {
		const ssize_t middle = start + (end - start) / 2;
		const int middle_val = ns[middle];

		if (middle_val > sought)
			end = middle;
		else
			start = middle + 1;
	}

	return end - 1;
}

int main()
{
	const std::vector ns = { 1, 3, 3, 3, 7, 9, 11, 11, 157 };

	for (const int n : ns) {
		std::cout << n << " -> [" << bsearch_leftmost(ns, n) << ", " <<
			bsearch(ns, n) << ", " << bsearch_rightmost(ns, n) << "]" << std::endl;
	}

	return 0;
}
