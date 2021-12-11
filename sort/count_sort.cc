// See https://www.interviewcake.com/question/cpp/top-scores?course=fc1&section=sorting-searching-logarithms

#include <iostream>
#include <vector>

std::vector<int> sort_scores(const std::vector<int>& scores, int maximum_score)
{
	// Count sort.
	std::vector<int> counts(maximum_score + 1);

	for (const int score : scores) {
		counts[score]++;
	}

	std::vector<int> ret;
	ret.reserve(scores.size());
	int index = 0;
	for (int i = 0; i < maximum_score + 1; i++) {
		for (int j = 0; j < counts[i]; j++) {
			ret.push_back(i);
		}
	}
	return ret;
}

int main()
{
	const auto sorted = sort_scores({ 100, 50, 75, 30, 1, 0, 19, 50, 50, 100, 1, 1, 1}, 100);

	for (const int score : sorted) {
		std::cout << score << " ";
	}
	std::cout << std::endl;

	return 0;
}
