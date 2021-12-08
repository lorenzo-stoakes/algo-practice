#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

int get_rand(int from, int to)
{
	return from + rand() % (to - from + 1);
}

void shuffle(std::vector<int>& ns)
{
	for (size_t i = 0; i < ns.size() - 1; i++) {
		size_t from_index = get_rand(i, ns.size() - 1);
		std::swap(ns[from_index], ns[i]);
	}
}

int main()
{
	std::vector<int> ns(100);
	for (int i = 0; i < 100; i++) {
		ns[i] = i + 1;
	}

	shuffle(ns);

	for (const int n : ns) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	return 0;
}
