#include <iostream>
#include <vector>

std::vector<int> merge_vecs(const std::vector<int>& vec_a,
			    const std::vector<int>& vec_b)
{
	size_t merged_size = vec_a.size() + vec_b.size();
	std::vector<int> ret(merged_size);

	size_t i = 0, j = 0;
	for (size_t k = 0; k < merged_size; k++) {
		if (i == vec_a.size())
			ret[k] = vec_b[j++];
		else if (j == vec_b.size())
			ret[k] = vec_a[i++];
		else if (vec_a[i] <= vec_b[j])
			ret[k] = vec_a[i++];
		else // vec_a[i] > vec_b[j]
			ret[k] = vec_b[j++];
	}

	return ret;
}

int main()
{
	const std::vector<int> my_vec {3, 4, 6, 10, 11, 15};
	const std::vector<int> alices_vec {1, 5, 8, 12, 14, 19};

	const std::vector<int> merged = merge_vecs(my_vec, alices_vec);

	for (const int n : merged) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	return 0;
}
