// See https://www.interviewcake.com/question/cpp/inflight-entertainment?course=fc1&section=hashing-and-hash-tables

#include <cassert>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

// Permitting a tolerance on movie length.
// Keep min/max values in bucket entries sized to tolerance.
struct range {
	int min = 0;
	int max = 0;
};

bool can_watch_two(int flight_length, int tolerance,
		   const std::vector<int> movie_lengths)
{
	// Divide into 'buckets' each `tolerance` in length.
	std::unordered_map<int, range> buckets;

	// General idea is we need to find a number at `target - tolerance` to
	// `target` range. This will either all be in the bucket containing our
	// target length (i.e. `flight_length - length`) or the one immediately
	// prior.

	// The 'trick' is to only store min/max in each range as this is
	// sufficient to determine what we need to know.

	for (const int length : movie_lengths) {
		if (length >= flight_length)
			continue;

		// Find the bucket containing our target length.
		int target = flight_length - length;
		const auto iter = buckets.find(target / tolerance);
		if (iter != buckets.cend() && iter->second.min <= target)
			return true;

		// Now check the bucket that contains our minimum target.
		int min_target = std::max(0, target - tolerance);
		const auto min_iter = buckets.find(min_target / tolerance);
		if (min_iter != buckets.cend() && min_iter->second.max >= min_target)
			return true;

		// Insert our value into the buckets.
		auto insert_iter = buckets.find(length / tolerance);
		if (insert_iter != buckets.cend()) {
			range& r = insert_iter->second;
			r.min = std::min(r.min, length);
			r.max = std::max(r.max, length);
		} else {
			buckets[length / tolerance] = { length, length };
		}
	}

	return false;
}

int main()
{
	assert(can_watch_two(57, 20, { 17, 19, 3, 21 }));
	assert(can_watch_two(60, 10, { 30, 20 }));

	return 0;
}
