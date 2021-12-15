// See https://www.interviewcake.com/question/cpp/largest-stack?course=fc1&section=queues-stacks
// (with bonus :)

#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

class max_stack
{
public:
	void push(const std::vector<int>& ns)
	{
		for (const int n : ns) {
			push(n);
		}
	}

	void push(int n)
	{
		if (n < 0)
			throw std::runtime_error("negative not supported!");

		if (m_size++ == 0) {
			m_max_stack.push_back(n);
			m_was_max = true;
			return;
		}

		// We use signs to indicate whether the last number was a max
		// number or not. If negative in m_stack that indicates next is
		// a max and vice-versa, if negative in m_max_stack indicates
		// next is not a max and vice-versa.
		if (m_was_max && n > m_max_stack.back()) {
			m_max_stack.push_back(n);
		} else if (m_was_max) { // n <= max
			m_stack.push_back(-n);
			m_was_max = false;
		} else if (n > m_max_stack.back()) { // !m_was_max
			m_max_stack.push_back(-n);
			m_was_max = true;
		} else { // !m_was_max && n <= max
			m_stack.push_back(n);
		}
	}

	int pop()
	{
		if (m_size-- == 0)
			throw std::runtime_error("stack overflow!");

		if (m_was_max) {
			int ret = m_max_stack.back();
			m_max_stack.pop_back();
			m_was_max = ret > 0;
			return abs(ret);
		} else {
			int ret = m_stack.back();
			m_stack.pop_back();
			m_was_max = ret < 0;
			return abs(ret);
		}
	}

	int get_max() const
	{
		if (m_size == 0)
			throw std::runtime_error("empty array!");

		return abs(m_max_stack.back());
	}

	size_t size() const
	{
		return m_size;
	}

	bool empty() const
	{
		return m_size == 0;
	}

private:
	size_t m_size = 0;
	bool m_was_max = false;

	std::vector<int> m_stack;
	std::vector<int> m_max_stack;
};

int main()
{
	max_stack stack;

	stack.push({ 6,1,1,7,6,1,1,8,8,1,1,2,10,11,12,1 });

	while (!stack.empty()) {
		int max = stack.get_max();
		std::cout << stack.pop() << " (" << max << ")" << std::endl;
	}

	return 0;
}
