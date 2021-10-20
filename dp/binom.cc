#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

int calc_binom(int n, int k)
{
	if (n < 1 || k < 1)
		return -1;

	int prev = n;
	for (int k2 = 2; k2 <= k; k2++) {
		// (n k) = (n k-1) * (n - k + 1) / k
		double val = (double)prev / k2;
		val *= n - k2 + 1;

		prev = std::round(val);
	}

	return prev;
}

int main()
{
	for (int n = 1; n <= 10; n++) {
		for (int k = 1; k <= n; k++) {
			std::cout << calc_binom(n, k) << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
