#include <iostream>
#include <limits>
#include <tuple>
#include <utility>
#include <vector>

// Returns start, end of max subarray.
std::tuple<int, int, int> max_subarray(const std::vector<int>& ns)
{
	int best_sum = std::numeric_limits<int>::min();
	int best_start = 0, best_end = 0;
	int sum = 0;

	int start = 0;
	for (int end = 0; end < ns.size(); end++) {
		const int num = ns[end];

		if (sum <= 0) {
			start = end;
			sum = num;
		} else {
			sum += num;
		}

		if (sum > best_sum) {
			best_sum = sum;
			best_start = start;
			best_end = end;
		}
	}

	return { best_start, best_end, best_sum };
}

int main()
{
	auto [ start, end, sum ] = max_subarray({ -100, 50, -3, 5000, 3, 9, -1 });

	std::cout << start << "->" << end << " sum: " << sum << std::endl;

	return 0;
}
