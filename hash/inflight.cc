// See https://www.interviewcake.com/question/cpp/inflight-entertainment?course=fc1&section=hashing-and-hash-tables

#include <cassert>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

bool can_watch_two(int flight_length, const std::vector<int> movie_lengths)
{
#if 1
	std::unordered_set<int> seen_lengths;

	for (const int length : movie_lengths) {
		if (seen_lengths.find(flight_length - length) !=
		    seen_lengths.end())
			return true;
		seen_lengths.insert(length);
	}

	return false;
#else
	// Less neat solution.

	std::unordered_map<int, int> movie_count;

	for (const int length : movie_lengths) {
		movie_count[length]++;
	}

	for (const int length : movie_lengths) {
		if (length >= flight_length)
			continue;

		const int other_length = flight_length - length;
		const auto iter = movie_count.find(other_length);
		if (iter == movie_count.cend())
			continue;

		if (length != other_length || iter->second > 1)
			return true;
	}

	return false;
#endif
}

int main()
{
	assert(!can_watch_two(1, { 2, 4 }));
	assert(!can_watch_two(2, { 2, 4 }));
	assert(!can_watch_two(4, { 2, 4 }));
	assert(can_watch_two(6, { 2, 4 }));
	assert(can_watch_two(4, { 2, 2, 3 }));
	assert(!can_watch_two(4, { 2, 3 }));

	return 0;
}
