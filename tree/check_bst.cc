#include <iostream>
#include <limits>
#include <vector>

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

// Recursive solution.
bool is_bst_recur(node *node, int min, int max)
{
	if (node->val < min || node->val > max)
		return false;

	if (node->left != nullptr &&
	    !is_bst_recur(node->left, min, node->val))
		return false;

	if (node->right != nullptr &&
	    !is_bst_recur(node->right, node->val + 1, max))
		return false;

	return true;
}

bool is_bst_iter(node *n)
{
	if (n->is_leaf())
		return true;

	std::vector<node *> stack;
	std::vector<int> min_stack;
	std::vector<int> max_stack;

	int min = std::numeric_limits<int>::min();
	int max = std::numeric_limits<int>::max();

	auto push_children = [&] {
		if (n->left != nullptr) {
			stack.push_back(n->left);
			min_stack.push_back(min);
			max_stack.push_back(n->val);
		}

		if (n->right != nullptr) {
			stack.push_back(n->right);
			min_stack.push_back(n->val + 1);
			max_stack.push_back(max);
		}
	};

	push_children();

	while (!stack.empty()) {
		n = stack.back();
		stack.pop_back();

		min = min_stack.back();
		min_stack.pop_back();

		max = max_stack.back();
		max_stack.pop_back();

		if (n->val < min || n->val > max)
			return false;

		push_children();
	} while (!stack.empty());

	return true;
}

#define USE_ITER

bool is_bst(node *head)
{
#ifdef USE_ITER
	return is_bst_iter(head);
#else
	return is_bst_recur(head,
			    std::numeric_limits<int>::min(),
			    std::numeric_limits<int>::max());
#endif
}

int main()
{
	node head(5);

	auto check_bst = [&] {
		if (is_bst(&head))
			std::cout << "is a BST";
		else
			std::cout << "is NOT a BST";
		std::cout << std::endl;
	};

	check_bst();
	head.left = new node(6);
	check_bst();
	head.left = new node(4);
	check_bst();
	head.right = new node(3);
	check_bst();
	head.right = new node(7);
	check_bst();
	head.left->left = new node(5);
	check_bst();
	head.left->left = new node(3);
	check_bst();
	head.left->left->right = new node(10);
	check_bst();
	head.left->left->right = new node(4);
	check_bst();

	return 0;
}
