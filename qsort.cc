#include <algorithm>
#include <iostream>
#include <vector>

namespace
{
template<typename T>
int partition(std::vector<T>& ns, int start, int end)
{
	int mid = (start + end) / 2;
	T mid_val = ns[mid];

	std::swap(ns[mid], ns[end]);

	int j = start;
	for (int i = start; i < end; i++) {
		if (ns[i] <= mid_val)
			std::swap(ns[i], ns[j++]);
	}

	std::swap(ns[end], ns[j]);

	return j;
}

template<typename T>
void qsort(std::vector<T>& ns, int start, int end)
{
	if (start >= end)
		return;

	int mid = partition(ns, start, end);

	qsort(ns, start, mid - 1);
	qsort(ns, mid + 1, end);
}

template<typename T>
void qsort(std::vector<T>& ns)
{
	qsort(ns, 0, ns.size() - 1);
}
}

int main()
{
	std::vector<int> ns;
	for (int i = 0; i < 100; i++) {
		ns.push_back(100 - i);
	}

	qsort(ns);

	for (int i = 0; i < 100; i++) {
		std::cout << ns[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
