// See https://www.interviewcake.com/question/cpp/recursive-string-permutations?course=fc1&section=dynamic-programming-recursion

#include <cstddef>
#include <iostream>
#include <unordered_set>

// Outrageously inefficient.

std::unordered_set<std::string> permute(const std::string& str)
{
	std::unordered_set<std::string> ret;

	if (str.size() <= 1) {
		ret.insert(str);
		return ret;
	}

	for (size_t i = 0; i < str.size(); i++) {
		std::string excluding = str.substr(0, i) + str.substr(i + 1);
		for (const std::string& rest : permute(std::move(excluding))) {
			ret.insert(std::string(1, str[i]) + rest);
		}
	}
	return ret;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		std::cerr << "usage: " << argv[0] << " [word]" << std::endl;
		return 1;
	}

	for (const std::string& str : permute(argv[1])) {
		std::cout << str << std::endl;
	}

	return 0;
}
