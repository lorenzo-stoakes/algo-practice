// See https://www.interviewcake.com/question/cpp/cafe-order-checker?course=fc1&section=array-and-string-manipulation

#include <iostream>
#include <vector>

bool first_come_first_served(const std::vector<int>& takeout_orders,
			     const std::vector<int>& dine_in_orders,
			     const std::vector<int>& served_orders)
{
	size_t i = 0, j = 0;

	for (const int n : served_orders) {
		if (i != takeout_orders.size() &&
		    takeout_orders[i] == n) {
			i++;
		} else if (j != dine_in_orders.size() &&
			   dine_in_orders[j] == n) {
			j++;
		} else {
			return false;
		}
	}

	return i == takeout_orders.size() && j == dine_in_orders.size();
}

int main()
{
	if (first_come_first_served({1,3,5}, {2,4,6}, {1,2,4,6,5,3}))
		std::cout << "1: ok" << std::endl;
	else
		std::cout << "1: NOT ok" << std::endl;

	if (first_come_first_served({17,8,24}, {12,19,2}, {17,8,12,19,24,2}))
		std::cout << "2: ok" << std::endl;
	else
		std::cout << "2: NOT ok" << std::endl;

	if (first_come_first_served({1,1,2}, {3,4,3}, {1,1,3,4,2,3}))
		std::cout << "3: ok" << std::endl;
	else
		std::cout << "3: NOT ok" << std::endl;

	return 0;
}
