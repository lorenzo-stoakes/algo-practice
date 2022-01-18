#include <array>
#include <iostream>
#include <vector>

int min_turns(const std::vector<int>& A, const std::vector<int>& B)
{
	std::array<int, 7> countsA = { 0 };
	std::array<int, 7> countsB = { 0 };

	int sumA = 0;
	for (const int a : A) {
		countsA[a]++;
		sumA += a;
	}

	int sumB = 0;
	for (const int b : B) {
		countsB[b]++;
		sumB += b;
	}

	bool largerA = sumA > sumB;
	int delta = largerA ? sumA - sumB : sumB - sumA;

	if (delta == 0)
		return 0;

	std::array<int, 7>& largerCounts = largerA ? countsA : countsB;
	std::array<int, 7>& smallerCounts = largerA ? countsB : countsA;

	int turns = 0;
	for (int i = 6; i >= 1; i--) {
		int deltaDelta = i - 1; // Turning dice gets us closer by up to i - 1.

		if (largerCounts[i] > 0) {
			for (int j = 0; j < largerCounts[i]; j++) {
				turns++;
				if (deltaDelta >= delta)
					return turns;
				delta -= deltaDelta;
			}
		}

		int opp = 7 - i;
		if (smallerCounts[opp] > 0) {
			for (int j = 0; j < smallerCounts[opp]; j++) {
				turns++;
				if (deltaDelta >= delta)
					return turns;
				delta -= deltaDelta;
			}
		}
	}

	return -1;
}

int main()
{
	std::cout << min_turns({5}, { 1, 1, 6 }) << std::endl;
	std::cout << min_turns({2,3,1,1,2}, { 5, 4, 6 }) << std::endl;
	std::cout << min_turns({5,4,1,2,6,5}, { 2 }) << std::endl;
	std::cout << min_turns({1,2,3,4,3,2,1}, { 6 }) << std::endl;

	return 0;
}
