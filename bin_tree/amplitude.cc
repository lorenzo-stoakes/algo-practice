#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

int min_amp(const std::vector<int>& ns, int k)
{
	std::set<int> set(ns.begin() + k, ns.end());

	int min = *set.begin();
	int max = *set.rbegin();
	int amp = max - min;

	for (int i = k; i < ns.size(); i++) {
		int prev = ns[i - k];
		int val = ns[i];

		set.insert(prev);
		set.erase(set.find(val));

		// TODO: Optimise
		min = *set.begin();
		max = *set.rbegin();
		int new_amp = max - min;
		if (new_amp < amp)
			amp = new_amp;
	}

	return amp;
}

int main()
{
	std::cout << min_amp({ 3,5,1,3,9,8 }, 4) << std::endl;

	return 0;
}
