#include <algorithm>
#include <iostream>
#include <vector>

void max_heap()
{
	std::cout << "max heap" << std::endl;

	std::vector<int> ns = { 6, 1, 4, 2, 3, 5 };
	std::make_heap(ns.begin(), ns.end());

	std::cout << "    top: " << ns.front() << std::endl;

	std::pop_heap(ns.begin(), ns.end());

	std::cout << "new top: " << ns.front() << std::endl;
	std::cout << "old top: " << ns.back() << std::endl;

	ns.pop_back();

	ns.push_back(10);
	std::push_heap(ns.begin(), ns.end());
	std::cout << "new top: " << ns.front() << std::endl;
}

void min_heap()
{
	std::cout << "min heap" << std::endl;

	std::vector<int> ns = { 6, 1, 4, 2, 3, 5 };
	std::make_heap(ns.begin(), ns.end(), std::greater<>{});

	std::cout << "    top: " << ns.front() << std::endl;

	std::pop_heap(ns.begin(), ns.end(), std::greater<>{});

	std::cout << "new top: " << ns.front() << std::endl;
	std::cout << "old top: " << ns.back() << std::endl;

	ns.pop_back();

	ns.push_back(0);
	std::push_heap(ns.begin(), ns.end(), std::greater<>{});
	std::cout << "new top: " << ns.front() << std::endl;
}

int main()
{
	max_heap();
	min_heap();

	return 0;
}
