#include <iostream>
#include <stdexcept>

struct node {
	node(int v) : val{v}, left{nullptr}, right{nullptr}
	{}

	int val;
	struct node *left, *right;

	bool is_leaf() const
	{
		return left == nullptr &&
			right == nullptr;
	}
};

int get_2nd_largest(node *node)
{
	if (node == nullptr || node->is_leaf())
		throw std::runtime_error("Invalid input");

	::node *parent = nullptr;
	while (node->right != nullptr) {
		parent = node;
		node = node->right;
	}

	// Leaf, our parent is the 2nd largest.
	if (node->left == nullptr)
		return parent->val;

	// We have values smaller than us, the largest of them is the 2nd
	// largest overall.
	node = node->left;
	while (node->right != nullptr) {
		node = node->right;
	}

	return node->val;
}

int main()
{

	node head(6);
	head.left = new node(3);

	std::cout << get_2nd_largest(&head) << std::endl;

	head.right = new node(8);
	std::cout << get_2nd_largest(&head) << std::endl;
	head.right->left = new node(7);
	std::cout << get_2nd_largest(&head) << std::endl;

	return 0;
}
