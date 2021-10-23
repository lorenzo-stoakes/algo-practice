#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

//#define PRINT_MATRIX

void print_matrix(const std::vector<std::vector<int>>& matrix)
{
	for (const auto& row : matrix) {
		for (int i = 1; i < row.size(); i++) {
			const int val = row[i];
			std::cout << val << " ";
		}
		std::cout << std::endl;
	}
}

// Items are [ size, val ] pairs.
int knapsack(const std::vector<std::pair<int, int>>& items, int Smax)
{
	if (items.empty() || Smax <= 0)
		return 0;

	// Initialised to zero.
	std::vector<std::vector<int>> A(items.size(), std::vector<int>(Smax + 1));

	// First row.
	int first_val = items[0].second;
	for (int i = items[0].first; i <= Smax; i++) {
		A[0][i] = first_val;
	}

	for (int i = 1; i < items.size(); i++) {
		auto [ size, val ] = items[i];

		for (int j = 1; j <= Smax; j++) {
			int excluded = A[i - 1][j];
			int included = j >= size ? val + A[i - 1][j - size] : 0;

			A[i][j] = std::max(excluded, included);
		}
	}

#ifdef PRINT_MATRIX
	print_matrix(A);
#endif

	return A[items.size() - 1][Smax];
}

int main()
{
	std::cout << knapsack({ { 10, 100 }, { 5, 50 }, { 4, 39 }, { 4, 39 }, { 4, 39 }, { 4, 39 }, { 4, 39 }, }, 20) << std::endl;

	return 0;
}
