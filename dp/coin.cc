// See https://www.interviewcake.com/question/cpp/coin?course=fc1&section=dynamic-programming-recursion

#include <cstdint>
#include <iostream>
#include <vector>

int64_t count_ways(int64_t amount, const std::vector<int>& denoms)
{
	std::vector<int> ways(amount + 1);
	ways[0] = 1;

	for (const int denom : denoms) {
		for (int i = denom; i <= amount; i++) {
			ways[i] += ways[i - denom];
		}
	}

	return ways[amount];
}

int main()
{
	std::cout << count_ways(4, { 1, 2, 3 }) << std::endl;

	return 0;
}
