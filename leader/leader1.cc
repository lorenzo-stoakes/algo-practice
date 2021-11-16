#include <iostream>
#include <vector>

int leader(const std::vector<int>& ns)
{
	// First, determine whether anything _potentially_ leads.
	int value = -1;
	int size = 0;
	for (const int n : ns) {
		if (size == 0) {
			size = 1;
			value = n;
			continue;
		}

		if (n == value)
			size++;
		else
			size--;
	}

	// Nothing leads.
	if (size == 0)
		return -1;

	int count = 0;
	for (const int n : ns) {
		if (n == value)
			count++;
	}

	if (count > ns.size() / 2)
		return value;

	return -1;
}

int main()
{
	std::cout << leader({ 1, 1, 2, 2, 3, 2, 2, 9, 2 }) << std::endl;

	return 0;
}
