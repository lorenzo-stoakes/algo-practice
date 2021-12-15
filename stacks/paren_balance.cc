// See https://www.interviewcake.com/question/cpp/bracket-validator?course=fc1&section=queues-stacks

#include <iostream>
#include <string>
#include <vector>

bool is_balanced(const std::string& str)
{
	std::vector<char> stack;

	for (const char chr : str) {
		switch (chr) {
		case '(':
		case '[':
		case '{':
			stack.push_back(chr);
			break;
		case ')':
			if (stack.empty() || stack.back() != '(')
				return false;
			stack.pop_back();
			break;
		case ']':
			if (stack.empty() || stack.back() != '[')
				return false;
			stack.pop_back();
			break;
		case '}':
			if (stack.empty() || stack.back() != '{')
				return false;
			stack.pop_back();
			break;
		default:
			return false;
		}
	}

	return true;
}

int main()
{
	if (!is_balanced("{[]()}"))
		std::cout << "failed 1" << std::endl;

	if (is_balanced("{[(])}"))
		std::cout << "failed 2" << std::endl;

	if (is_balanced("{[}"))
		std::cout << "failed 3" << std::endl;

	return 0;
}
