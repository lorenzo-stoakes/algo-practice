// See https://www.interviewcake.com/question/cpp/stock-price?course=fc1&section=greedy

#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

int get_best_profit(const std::vector<int>& prices)
{
	if (prices.size() < 2)
		throw std::runtime_error("Invalid price data");

	int min = prices[0];
	int best_profit = prices[1] - prices[0];

	for (size_t i = 1; i < prices.size(); i++) {
		const int price = prices[i];

		best_profit = std::max(best_profit, price - min);
		min = std::min(min, price);
	}

	return best_profit;
}

int main()
{
	std::cout << get_best_profit({ 10, 7, 5, 8, 11, 9 }) << std::endl;
	std::cout << get_best_profit({ 10, 5, 4, 1 }) << std::endl;
}
