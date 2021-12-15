// See https://www.interviewcake.com/question/cpp/matching-parens?course=fc1&section=queues-stacks

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class paren_finder
{
public:
	paren_finder(const std::string& str)
	{
		std::vector<int> stack;

		for (int i = 0; i < str.size(); i++) {
			const char chr = str[i];
			switch (chr) {
			case '(':
				stack.push_back(i);
				break;
			case ')':
			{
				int start = stack.back();
				stack.pop_back();
				m_open_to_close[start] = i;
				break;
			}
			default:
				break;
			}
		}
	}

	int find_paren_end(int from)
	{
		const auto iter = m_open_to_close.find(from);
		if (iter == m_open_to_close.cend())
			return -1;

		return iter->second;
	}

private:
	std::unordered_map<int, int> m_open_to_close;
};

int find_close_paren(const std::string& str, int open)
{
	std::vector<int> stack;

	for (int i = 0; i < str.size(); i++) {
		const char chr = str[i];
		switch (chr) {
		case '(':
			stack.push_back(i);
			break;
		case ')':
		{
			int start = stack.back();
			stack.pop_back();

			if (start == open)
				return i;
			break;
		}
		default:
			break;
		}
	}

	return -1;
}
int find_close_paren_fast(const std::string& str, int open)
{
	int open_parens = 1;

	for (int i = open + 1; i < str.size(); i++) {
		const char chr = str[i];
		switch (chr) {
		case '(':
			open_parens++;
			break;
		case ')':
			open_parens--;
			if (open_parens == 0)
				return i;

			break;
		default:
			break;
		}
	}

	return -1;
}

int main()
{
	const std::string str =
		"Sometimes (when I nest them (my parentheticals) too much (like this (and this))) they get confusing.";

	paren_finder finder(str);
	std::cout << finder.find_paren_end(10) << std::endl;
	std::cout << find_close_paren(str, 10) << std::endl;
	std::cout << find_close_paren_fast(str, 10) << std::endl;

	return 0;
}
