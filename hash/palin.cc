#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

bool is_permut_palin_cleaner(const std::string& str)
{
	std::unordered_set<char> unpaired;

	for (const char chr : str) {
		if (unpaired.find(chr) != unpaired.end())
			unpaired.erase(chr);
		else
			unpaired.insert(chr);
	}

	return unpaired.size() <= 1;
}

bool is_permut_palin(const std::string& str)
{
	if (str.empty())
		return false;

	std::unordered_map<char, int> counts;

	for (const char chr : str) {
		counts[chr]++;
	}

	bool expected_odd = str.size() % 2 == 1;

	for (auto [ chr, count ] : counts) {
		if (count % 2 == 0)
			continue;

		if (!expected_odd)
			return false;
		expected_odd = false;
	}

	return !expected_odd;
}

int main()
{
	std::vector<std::string> strs = { "civic", "ivicc", "civil", "livci", "nnaa" };

	for (const std::string& str : strs) {
		std::cout << str << ": " <<
			(is_permut_palin_cleaner(str) ? "YES" : "NO") <<
			std::endl;
	}

	return 0;
}
