#include <iostream>
#include <limits>
#include <vector>

constexpr int MAX = std::numeric_limits<int>::max();

int min_weight(const std::vector<std::vector<int>>& triangle)
{
	if (triangle.empty())
		return 0;

	std::vector<std::vector<int>> copy = triangle;

	int min = copy[0][0];

	for (int i = 1; i < copy.size(); i++) {
		const auto& row = copy[i];

		min = MAX;
		for (int j = 0; j < row.size(); j++) {
			int left = j > 0 ? copy[i - 1][j - 1] : MAX;
			int right = j < row.size() - 1 ? copy[i - 1][j] : MAX;
			copy[i][j] += std::min(left, right);

			if (copy[i][j] < min)
				min = copy[i][j];
		}
	}

	return min;
}

int main()
{
	std::vector<std::vector<int>> t = {   { 2 },
					    { 4, 4, },
					   { 8, 5, 6 },
					  { 4, 2, 6, 2 },
				         { 1, 5, 2, 3, 4 } };

	std::cout << min_weight(t) << std::endl;
}
