#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>

void reverse_string(std::string& str, ssize_t from, ssize_t to)
{
	while (from < to) {
		std::swap(str[from++], str[to--]);
	}
}

void reverse_words(std::string& str)
{
	// Reverse entire string.
	reverse_string(str, 0, str.size() - 1);

	size_t from = 0, to = 0;
	for (ssize_t to = 1; to < str.size(); to++) {
		if (str[to] == ' ') {
			reverse_string(str, from, to - 1);
			from = to + 1;
			to++;
		}
	}

	// Grab last word.
	reverse_string(str, from, str.size() - 1);
}

int main()
{
	std::string str = "cake pound steal";
	reverse_words(str);
	std::cout << str << std::endl;

	return 0;
}
