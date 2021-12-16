#include <iostream>

struct node
{
	node(int val) : val{val}
	{}

	int val;
	node *next = nullptr;
};

node *kth_last(node *head, int k)
{
	if (head == nullptr)
		return nullptr;

	node *kth = head;
	node *end = head;

	// Offset `kth` and `end` `k` apart.
	for (int i = 0; i < k; i++) {
		if (end->next == nullptr)
			return nullptr;

		end = end->next;
	}

	// Now find end. Then `kth` will be the kth from end.
	while (end->next != nullptr) {
		kth = kth->next;
		end = end->next;
	}

	return kth;
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

	for (int i = 0; i < 5; i++) {
		std::cout << kth_last(&one, i)->val << std::endl;
	}

	return 0;
}
