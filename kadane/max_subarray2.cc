#include <algorithm>
#include <iostream>
#include <limits>

int max_subarray(const std::vector<int>& ns)
{
	int best_ending_here = 0;
	int best = std::numeric_limits<int>::min();

	for (const int n : ns) {
		best_ending_here = std::max(0, best_ending_here + n);
		best = std::max(best, best_ending_here);
	}

	return best;
}

int max_subarray2(const std::vector<int>& ns, int& best_start, int& best_end)
{
	int best_ending_here = 0;

	int sum = 0, best_sum = std::numeric_limits<int>::min();
	std::size_t start = 0;
	for (std::size_t i = 0; i < ns.size(); i++) {
		const int end = i;
		const int n = ns[i];

		// Not worth keeping if the sum is already negative.
		if (sum <= 0) {
			start = end;
			sum = n;
		} else {
			// Otherwise add y'all on.
			sum += n;
		}

		if (sum > best_sum) {
			best_sum = sum;
			best_start = start;
			best_end = end;
		}
	}

	return best_sum;
}

int max_subarray3(const std::vector<int>& ns)
{
	int best_ending_here = 0;
	int best = std::numeric_limits<int>::min();

	for (const int n : ns) {
		if (best_ending_here <= 0)
			best_ending_here = n;
		else
			best_ending_here += n;

		best = std::max(best, best_ending_here);
	}

	return best;
}

int main()
{
	int best_start, best_end;

	std::cout << max_subarray3({ 1000, 50, -500, 1000000, -1 }) << std::endl;
	//std::cout << max_subarray2({ 1000, 50, -500, 1000000, -1, -1000000000, 10000000 }, best_start, best_end) << std::endl;
	//std::cout << "In range [" << best_start << ", " << best_end << "]" << std::endl;

	return 0;
}
