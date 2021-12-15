// See https://www.interviewcake.com/question/cpp/queue-two-stacks?course=fc1&section=queues-stacks

#include <iostream>
#include <stdexcept>
#include <vector>

class queue
{
public:
	void enqueue(int n)
	{

		m_enqueue_stack.push_back(n);
		m_size++;
	}

	int dequeue()
	{
		if (m_size == 0)
			throw std::runtime_error("empty!");

		if (m_dequeue_stack.empty()) {
			while (!m_enqueue_stack.empty()) {
				int n = m_enqueue_stack.back();
				m_enqueue_stack.pop_back();
				m_dequeue_stack.push_back(n);
			}
		}

		int ret = m_dequeue_stack.back();
		m_dequeue_stack.pop_back();
		m_size--;
		return ret;
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

	std::vector<int> m_dequeue_stack, m_enqueue_stack;
};

int main()
{
	queue q;
	for (int i = 0; i < 1000000; i++) {
		q.enqueue(i + 1);
		q.dequeue();
		q.enqueue(i + 1);
	}

	return 0;
}
