// See https://www.interviewcake.com/question/cpp/delete-node?course=fc1&section=linked-lists

#include <iostream>
#include <stdexcept>

struct node
{
	node(int val) : val{val}
	{}

	int val;
	node *next = nullptr;
};

void delete_node(node *del_node)
{
	if (del_node->next == nullptr)
		throw std::runtime_error("Can't delete last node!");

	*del_node = *del_node->next;
}

int main()
{
	node one = node(1);
	node two = node(2);
	node three = node(3);
	one.next = &two;
	two.next = &three;

	auto print_nodes = [&] {
		for (node *n = &one; n != nullptr; n = n->next) {
			std::cout << n->val << std::endl;
		}
	};

	print_nodes();
	delete_node(&two);
	std::cout << "---" << std::endl;
	print_nodes();

	return 0;
}
