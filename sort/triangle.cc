#include <algorithm>
#include <iostream>
#include <vector>

int detect_triangle(std::vector<int>& A)
{
    if (A.size() < 3)
        return 0;

    // The criteria amounts to 'are the sum of 2 of the 3 elements greater than the other?'
    // Thus we can consider any 3 elements in any order.

    std::sort(A.begin(), A.end());

    for (size_t i = 0; i < A.size() - 2; i++) {
        long first = A[i];
        long second = A[i+1];
        long third = A[i+2];

        // first + third > second : third > second so yes.
        // second + third > first : first < second < third so yes.

        if (first + second > third)
            return 1;

        // If first + second <= third, then they will also be <= all remaining values. We discard first as the smallest value.
    }

    return 0;
}

int main()
{
	std::vector<int> triangle1 = {10, 2, 5, 1, 8, 20};
	std::vector<int> triangle2 = {10, 50, 5, 1};

	std::cout << detect_triangle(triangle1) << std::endl;
	std::cout << detect_triangle(triangle2) << std::endl;

	return 0;
}
