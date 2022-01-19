/*
 *
 * Given an array of n strings with length m return true if there is one pair
 * such that there is only one difference between the words, e.g, abcd and abce
 * would yield true, but abcd and abdd[sic] (probable error, should be abde)
 * would be false.
 *
 * https://www.careercup.com/question?id=5646898097029120
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

bool contains_close_pair(const std::vector<std::string>& strs)
{
	if (strs.empty())
		return false;

	const size_t size = strs.size();
	const int m = strs[0].size();

	std::vector<std::unordered_map<char, std::unordered_set<char>>> trie(m);

	for (const std::string& str : strs) {
		int count = 0;
		for (int i = 0; i < str.size() - 1; i++) {
			const char chr = str[i];
			const char next = str[i+1];

			auto& level = trie[i];
			auto iter = level.find(chr);
			if (iter == level.end()) {
				level[chr].insert(next);
				count++;
				continue;
			}

			auto& set = iter->second;
			if (set.find(next) == set.end()) {
				set.insert(next);
				count++;
			}
		}
		if (count <= 1)
			return true;
	}

	return false;
}

int main()
{
	std::cout << contains_close_pair({ "abcd", "abce" }) << std::endl; // should be 1
	std::cout << contains_close_pair({ "abcd", "abde" }) << std::endl; // 0
	std::cout << contains_close_pair({ "abcd", "abde", "xacb", "xyza", "xycg" }) << std::endl; // 0
	std::cout << contains_close_pair({ "abcd", "abde", "xacb", "xyza", "xycb" }) << std::endl; // 1

	return 0;
}
