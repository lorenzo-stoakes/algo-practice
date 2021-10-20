#include <iostream>
#include <vector>

int calc_routes(int m, int n)
{
	if (m == 0 || n == 0)
		return 0;

	// 2D array where A[i][j] = number of unique routes from top left to
	// bottom right for 2D array of size (i + 1, j + 1).
	std::vector<std::vector<int>> num_routes(m, std::vector<int>(n));

	num_routes[0][0] = 1;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int curr = num_routes[i][j];

			if (i < m - 1)
				num_routes[i + 1][j] += curr;

			if (j < n - 1)
				num_routes[i][j + 1] += curr;
		}
	}

	return num_routes[m - 1][n - 1];
}

int calc_routes(int m)
{
	return calc_routes(m, m);
}

int main()
{
	for (int i = 1; i <= 10; i++) {
		std::cout << i << "\t" << calc_routes(i) << std::endl;
	}
}
