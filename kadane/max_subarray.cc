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
	int current_sum = 0;

	int current_start = 0;
	for (int current_end = 0; current_end < ns.size(); current_end++) {
		const int num = ns[current_end];

		if (current_sum <= 0) {
			current_start = current_end;
			current_sum = num;
		} else {
			current_sum += num;
		}

		if (current_sum > best_sum) {
			best_sum = current_sum;
			best_start = current_start;
			best_end = current_end;
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
