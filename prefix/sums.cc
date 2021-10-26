#include <iostream>
#include <vector>

namespace
{
std::vector<int> gen_prefixes(const std::vector<int>& nums)
{
	std::vector<int> ret(nums.size() + 1);

	int i = 1;
	for (const int num : nums) {
		ret[i] = ret[i-1] + num;
		i++;
	}

	return ret;
}

int calc_sum(const std::vector<int>& prefixes, int from, int to)
{
	return prefixes[to + 1] - prefixes[from];
}

std::vector<int> calc_sums(const std::vector<int>& nums,
			   const std::vector<std::pair<int, int>>& ranges)
{
	std::vector<int> prefixes = gen_prefixes(nums);

	std::vector<int> ret(ranges.size());

	int i = 0;
	for (const auto [ from, to ] : ranges) {
		ret[i++] = calc_sum(prefixes, from, to);
	}

	return ret;
}
}

int main()
{
	for (const int n : calc_sums({ 1, 2, 3, 10, 9, 8 }, { { 0, 0 }, { 0, 2 }, { 2, 3 }, { 0, 5 } })) {
		std::cout << n << std::endl;
	}

	return 0;
}
