#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

// Rough attempt at knapsack 0/1.

int best_fit(const std::vector<std::pair<int, int>>& weight_val_pairs,
	     int size)
{
	std::vector<int> so_far_val(size + 1);
	std::vector<std::unordered_set<int>> so_far(size + 1);

	for (int i = 0; i <= size; i++) {
		int max_val = 0;
		int max_index = -1;

		// TODO: Make more efficient/clean up.
		if (i > 0) {
			max_val = so_far_val[i-1];
			so_far_val[i] = so_far_val[i-1];
			so_far[i] = so_far[i-1];
		}

		for (int j = 0; j < weight_val_pairs.size(); j++) {
			int weight = weight_val_pairs[j].first;
			if (weight > i)
				continue;

			int val = weight_val_pairs[j].second;

			const auto& prev_set = so_far[i - weight];
			if (prev_set.find(weight) != prev_set.end())
				continue;

			int candidate = val + so_far_val[i - weight];

			if (candidate > max_val) {
				max_val = candidate;
				max_index = j;
			}
		}

		if (max_index == -1)
			continue;

		const auto& pair = weight_val_pairs[max_index];
		so_far[i] = so_far[i - pair.first];
		so_far[i].insert(pair.first);
		so_far_val[i] = max_val;
	}

	return so_far_val[size];
}

int main()
{
	// 0  1  2   3   4   5     6     7     8     9     10    11    12
	// 0  0  15  150 150 165   165   165   165   175   310   310   325
	// [] [] [2] [3] [3] [2,3] [2,3] [2,3] [2,3] [2,7] [3,7] [3,7] [2,3,7]

	for (int i = 0; i <= 12; i++) {
		std::cout << best_fit({ { 7, 160 }, { 2, 15 }, { 3, 150 } },
				      i) << std::endl;
	}

	return 0;
}
