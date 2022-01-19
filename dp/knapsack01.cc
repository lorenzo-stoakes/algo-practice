#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

// First rough attempt.
int rough_fit(const std::vector<std::pair<int, int>>& weight_val_pairs,
	     int size)
{
	std::vector<int> so_far_val(size + 1);
	// Iffy...
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

// Use full dynamic programming table.
int best_fit1(const std::vector<std::pair<int, int>>& weight_val_pairs,
	      int max_weight)
{
	const size_t size = weight_val_pairs.size();

	// Each row i contains items [0, i).
	// Each column represents a weight limit.
	std::vector<std::vector<int>> table(size + 1);
	for (auto& row : table) {
		row = std::vector<int>(max_weight + 1);
	}

	for (size_t item = 1; item <= size; item++) {
		const auto [ weight, val ] = weight_val_pairs[item - 1];
		for (int limit = 0; limit <= max_weight; limit++) {
			if (weight > limit)
				table[item][limit] = table[item - 1][limit];
			else
				table[item][limit] = std::max(
					table[item - 1][limit],
					table[item - 1][limit - weight] + val);
		}
	}

	return table[size][max_weight];
}

// But we don't need the full table, we can just use two rows.
int best_fit(const std::vector<std::pair<int, int>>& weight_val_pairs,
	     int max_weight)
{
	const size_t size = weight_val_pairs.size();

	std::vector<int> so_far(max_weight + 1);
	auto prev = so_far;

	for (const auto [ weight, val ] : weight_val_pairs) {
		for (int limit = weight; limit <= max_weight; limit++) {
			const int new_val = prev[limit - weight] + val;
			so_far[limit] = std::max(prev[limit], new_val);
		}
		prev = so_far;
	}

	return so_far[max_weight];
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
