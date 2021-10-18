#include <iostream>
#include <limits>
#include <string>
#include <vector>

//#define PRINT_ARR

void print_arr(const std::vector<std::vector<int>>& A)
{
	for (int j = 0; j < A[0].size(); j++) {
		for (int i = 0; i < A.size(); i++) {
			std::cout << A[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int levin(const std::string& word, const std::string& target)
{
	// Weird edge cases.
	if (word.size() == 0)
		return target.size();
	if (target.size() == 0)
		return word.size();

	std::vector<std::vector<int>> A(word.size() + 1, std::vector<int>(target.size() + 1));

	for (int y = 0; y <= target.size(); y++) {
		for (int x = 0; x <= word.size(); x++) {
			if (x == 0 && y == 0)
				continue;

			int min = std::numeric_limits<int>::max();
			// Deletion
			if (x > 0 && A[x-1][y] + 1 < min)
				min = A[x-1][y] + 1;
			// Insertion
			if (y > 0 && A[x][y-1] + 1 < min)
				min = A[x][y-1] + 1;
			// Change/pass
			if (x > 0 && y > 0) {
				int val = A[x-1][y-1];
				val += word[x-1] == target[y-1] ? 0 : 1;

				if (val < min)
					min = val;
			}

			if (min == std::numeric_limits<int>::max())
				min = 0;

			A[x][y] = min;
		}
	}


#ifdef PRINT_ARR
	print_arr(A);
#endif

	return A[word.size()][target.size()];
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		std::cerr << "usage: " << argv[0] << " [word] [target]" << std::endl;
		return 1;
	}

	std::cout << levin(argv[1], argv[2]) << std::endl;

	return 0;
}
