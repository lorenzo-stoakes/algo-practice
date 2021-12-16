#include <iostream>

struct node
{
	node(int val) : val{val}
	{}

	int val;
	node *next = nullptr;
};

bool contains_cycle(node *head)
{
	node *slow = head;
	if (slow == nullptr)
		return false;

	node *fast = head->next;
	while (slow != nullptr && fast != nullptr) {
		if (slow == fast)
			return true;

		slow = slow->next;
		fast = fast->next;
		if (fast == nullptr)
			return false;
		fast = fast->next;
	}

	return false;
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

	if (contains_cycle(&one))
		std::cout << "1: FAIL" << std::endl;

	two.next = &one;

	if (!contains_cycle(&one))
		std::cout << "2: FAIL" << std::endl;

	two.next = &two;

	if (!contains_cycle(&one))
		std::cout << "3: FAIL" << std::endl;

	two.next = &three;
	five.next = &one;

	if (!contains_cycle(&one))
		std::cout << "4: FAIL" << std::endl;

	return 0;
}
