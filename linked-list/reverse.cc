#include <iostream>

struct node
{
	node(int val) : val{val}
	{}

	int val;
	node *next = nullptr;
};

node *reverse(node* head)
{
	node *prev = nullptr;
	node *curr = head;
	node *next;

	while (curr != nullptr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	return prev;
}

int main()
{
	node one = node(1);
	node two = node(2);
	node three = node(3);
	node four = node(4);
	node five = node(5);

	one.next = &two;
	two.next = &three;
	three.next = &four;
	four.next = &five;

	for (node *curr = reverse(&one); curr != nullptr; curr = curr->next) {
		std::cout << curr->val << std::endl;
	}

	return 0;
}
