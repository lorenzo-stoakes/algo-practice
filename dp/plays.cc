#include <iostream>
#include <vector>
#include <unordered_map>

#define USE_MEMO
#define PRINT_ARRAY

#ifdef USE_MEMO
std::vector<std::unordered_map<int, int>> memo;
#endif

void print_array(const std::vector<std::vector<int>>& A)
{
	for (const auto& row : A) {
		for (int val : row) {
			std::cout << val << " ";
		}
		std::cout << std::endl;
	}
}

int count_combins1(const std::vector<int>& plays, int score, int offset)
{
	if (score < 0)
		return 0;
	if (score == 0)
		return 1;

#ifdef USE_MEMO
	const auto iter = memo[offset].find(score);
	if (iter != memo[offset].cend())
		return iter->second;
#endif

	int sum = 0;
	for (int i = offset; i < plays.size(); i++) {
		sum += count_combins1(plays, score - plays[i], i);
	}

#ifdef USE_MEMO
	memo[offset][score] = sum;
#endif
	return sum;
}

int count_combins1(const std::vector<int>& plays, int score)
{
	return count_combins1(plays, score, 0);
}

int count_combins2(const std::vector<int>& plays, int score)
{
	std::vector<std::vector<int>> A(plays.size(), std::vector<int>(score + 1));

	// Prepopulate for 1st play.
	for (int j = 0; j <= score; j += plays[0]) {
		A[0][j] = 1;
	}

	for (int i = 1; i < plays.size(); i++) {
		for (int j = 0; j <= score; j++) {
			// Consisting of plays[0..i -1] only.
			A[i][j] = A[i - 1][j];

			// Actually O(s^2n) :'(
			for (int k = j - plays[i]; k >= 0; k -= plays[i]) {
				A[i][j] += A[i - 1][k];
			}
		}
	}

#ifdef PRINT_ARRAY
	print_array(A);
#endif

	return A[plays.size() - 1][score];
}

int count_combins3(const std::vector<int>& plays, int score)
{
	std::vector<std::vector<int>> A(plays.size(), std::vector<int>(score + 1));

	// Prepopulate for 1st play.
	for (int j = 0; j <= score; j += plays[0]) {
		A[0][j] = 1;
	}

	for (int i = 1; i < plays.size(); i++) {
		for (int j = 0; j <= score; j++) {
			// Consisting of plays[0..i -1] only.
			A[i][j] = A[i - 1][j];
			A[i][j] += j >= plays[i] ? A[i][j - plays[i]] : 0;
		}
	}

#ifdef PRINT_ARRAY
	print_array(A);
#endif

	return A[plays.size() - 1][score];
}

int count_combins4(const std::vector<int>& plays, int score)
{
	std::vector<std::vector<int>> A(plays.size(), std::vector<int>(score + 1));

	for (int i = 0; i < plays.size(); i++) {
		A[i][0] = 1; // Always 1 way of getting to 0 score.

		for (int j = 1; j <= score; j++) {
			A[i][j] = i > 0 ? A[i - 1][j] : 0;
			A[i][j] += j >= plays[i] ? A[i][j - plays[i]] : 0;
		}
	}

#ifdef PRINT_ARRAY
	print_array(A);
#endif

	return A[plays.size() - 1][score];
}

int main()
{
	std::vector<int> plays = { 2, 3, 7 };

#ifdef USE_MEMO
	for (int i = 0; i < plays.size(); i++) {
		memo.push_back({});
	}
#endif

	std::cout << count_combins4(plays, 12) << std::endl;

	return 0;
}
