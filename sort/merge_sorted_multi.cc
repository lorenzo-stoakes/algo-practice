#include <iostream>
#include <limits>
#include <vector>

std::vector<int> merge_multi(const std::vector<std::vector<int>>& vecs)
{
	size_t merged_size = 0;
	for (const auto& vec : vecs) {
		merged_size += vec.size();
	}
	if (merged_size == 0)
		return {};

	std::vector<int> ret(merged_size);

	std::vector<size_t> counters(vecs.size());
	for (size_t k = 0; k < merged_size; k++) {
		int min = std::numeric_limits<int>::max();
		size_t min_vec_index = 0;
		for (size_t i = 0; i < vecs.size(); i++) {
			const auto& vec = vecs[i];
			size_t counter = counters[i];

			if (counter == vec.size())
				continue;

			int val = vec[counter];
			if (val <= min) {
				min = val;
				min_vec_index = i;
			}
		}
		ret[k] = vecs[min_vec_index][counters[min_vec_index]++];
	}

	return ret;
}

int main()
{
	const std::vector<int> my_vec {3, 4, 6, 10, 11, 15};
	const std::vector<int> alices_vec {1, 5, 8, 12, 14, 19};
	const std::vector<int> steves_vec {2, 7, 9, 13, 16, 17, 18};

	std::vector<std::vector<int>> combined = {my_vec, alices_vec, steves_vec};

	for (const int n : merge_multi(combined)) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	return 0;
}
