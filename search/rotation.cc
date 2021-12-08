// See https://www.interviewcake.com/question/cpp/find-rotation-point?course=fc1&section=sorting-searching-logarithms

#include <iostream>
#include <string>
#include <vector>

int get_rotation_point(const std::vector<std::string>& words)
{
	int from = 0, to = words.size() - 1;

	while (from <= to) {
		int mid = (from + to) / 2;

		const std::string& word = words[mid];

		int prev_index = mid == 0 ? words.size() - 1 : mid - 1;
		if (word < words[prev_index])
			return mid;

		 if (word >= words[to]) {
			 from = mid;
		 } else {
			 to = mid;
		 }
	}

	return -1;
}

int main()
{
	std::vector<std::string> words = {
		"ptolemaic",
		"retrograde",
		"supplant",
		"undulate",
		"xenoepist",
		"asymptote",  // <-- rotates here! (5)
		"babka",
		"banoffee",
		"engender",
		"karpatka",
		"othellolagkage",
	};

	std::cout << get_rotation_point(words) << std::endl;

	return 0;
}
