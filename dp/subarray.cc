#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

namespace
{
/*
int max_subarray1(const std::vector<int>& ns, int begin, int end)
{
	if (begin > end)
		return 0;

	if (begin == end)
		return ns[begin];

	int max = std::numeric_limits<int>::min();
	for (int i = begin; i <= end; i++) {

	}
}
*/

// O(n^3)
int max_subarray1(const std::vector<int>& ns)
{
	int max = std::numeric_limits<int>::min();

	for (int i = 0; i < ns.size(); i++) {
		for (int j = i; j < ns.size(); j++) {
			int sum = 0;
			for (int k = i; k <= j; k++) {
				sum += ns[k];
			}

			if (sum > max)
				max = sum;
		}
	}

	return max;
}

// O(n^2)
int max_subarray2(const std::vector<int>& ns)
{
	int max = std::numeric_limits<int>::min();

	for (int i = 0; i < ns.size(); i++) {
		int sum = ns[i];
		if (sum > max)
			max = sum;

		for (int j = i + 1; j < ns.size(); j++) {
			sum += ns[j];
			if (sum > max)
				max = sum;
		}
	}

	return max;
}

// O(n)
int max_subarray3(const std::vector<int>& ns)
{
	if (ns.empty())
		return 0;


	int max = std::numeric_limits<int>::min();

	int prev = 0;
	for (int n : ns) {
		int next = std::max(n, n + prev);
		max = std::max(max, next);

		prev = next;
	}

	return max;
}

} // namespace

#define NUM_ITERS (100)
#define NUM_ELEMENTS (10)

int main()
{
	for (int i = 0; i < NUM_ITERS; i++) {
		std::vector<int> ns;
		ns.reserve(NUM_ELEMENTS);

		for (int j = 0; j < NUM_ELEMENTS; j++) {
			int n = rand() % 201;
			ns.push_back(n - 100);
		}

		int res1 = max_subarray1(ns);
		int res2 = max_subarray2(ns);
		int res3 = max_subarray3(ns);

		if (res1 != res2 || res2 != res3) {
			std::cout << "Mismatch!" << std::endl;
			return 1;
		}
	}

	return 0;
}
