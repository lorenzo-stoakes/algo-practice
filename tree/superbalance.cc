// See https://www.interviewcake.com/question/cpp/balanced-binary-tree?course=fc1&section=trees-graphs

#include <iostream>
#include <deque>

struct node {
	node(int v) : value{v}, left{nullptr}, right{nullptr}
	{}

	int value;
	struct node *left, *right;

	bool is_leaf() const
	{
		return left == nullptr &&
			right == nullptr;
	}
};

bool is_superbalanced(node *n)
{
	// BFS to each depth level.
	std::deque<node *> queue;
	if (n->left != nullptr)
		queue.push_back(n->left);

	if (n->right != nullptr)
		queue.push_back(n->right);

	int depth = 1, last_leaf_depth = 0;
	bool seen_leaf = false;
	for (; !queue.empty(); depth++) {
		n = queue.front();
		queue.pop_front();

		if (n->left != nullptr)
			queue.push_back(n->left);
		if (n->right != nullptr)
			queue.push_back(n->right);

		if (!n->is_leaf())
			continue;

		// Is a leaf.
		if (!seen_leaf) {
			last_leaf_depth = depth;
			seen_leaf = true;
			continue;
		}

		if (depth - last_leaf_depth > 1)
			return false;
	}

	return true;
}

int main()
{
	node head(1);
	node two(2), three(3), four(4), five(5);

	auto print_balance = [&] {
		if (is_superbalanced(&head))
			std::cout << "balanced";
		else
			std::cout << "unbalanced";
		std::cout << std::endl;
	};

	head.left = &two;
	print_balance();
	two.right = &three;
	print_balance();
	head.right = &four;
	print_balance();
	three.left = &five;
	print_balance();

	return 0;
}
