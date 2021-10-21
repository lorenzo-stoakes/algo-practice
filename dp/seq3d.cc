#include <deque>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

using Array2D = std::vector<std::vector<int>>;

struct pair_hash
{
	template <typename T1, typename T2>
	std::size_t operator() (const std::pair<T1, T2> &pair) const
	{
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

void find_entries(const Array2D& arr, std::deque<std::pair<int, int>>& q,
		  int target)
{
	int i = 0;
	for (const auto& row : arr) {
		int j = 0;
		for (const int val : row) {
			if (val == target)
				q.push_back({ i, j });

			j++;
		}
		i++;
	}

}

void reaches_target(const Array2D& arr, std::deque<std::pair<int, int>>& q,
		    std::unordered_set<std::pair<int, int>, pair_hash>& seen,
		    int x, int y, int target)
{
	if (x < 0 || x >= arr.size() || y < 0 || y >= arr[x].size())
		return;

	if (arr[x][y] == target && seen.find({ x, y }) == seen.end()) {
		q.push_back({x, y});
		seen.insert({x, y});
	}
}

bool contains_sequence(const Array2D& arr, const std::vector<int>& seq)
{
	if (seq.empty())
		return false;

	std::deque<std::pair<int, int>> q;
	find_entries(arr, q, seq[0]);

	for (int i = 1; i < seq.size(); i++) {
		int target = seq[i];

		if (q.empty())
			return false;

		std::unordered_set<std::pair<int, int>, pair_hash> seen;
		int qsize = q.size();
		for (int j = 0; j < qsize; j++) {
			auto [ x, y ] = q.front();
			q.pop_front();

			reaches_target(arr, q, seen, x - 1, y, target); // Left
			reaches_target(arr, q, seen, x + 1, y, target); // Right
			reaches_target(arr, q, seen, x, y - 1, target); // Up
			reaches_target(arr, q, seen, x, y + 1, target); // Down
		}
	}


	return q.size() > 0;
}

int main()
{
	Array2D arr = { { 1, 2, 3 }, { 1, 2, 5 }, { 8, 3, 4 } };
	std::vector<int> seq = { 1, 2, 3, 4, 5 };

	if (contains_sequence(arr, seq))
		std::cout << "aye" << std::endl;
	else
		std::cout << "nay" << std::endl;

	return 0;
}
