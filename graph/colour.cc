// See https://www.interviewcake.com/question/cpp/graph-coloring?course=fc1&section=trees-graphs

#include <algorithm>
#include <deque>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

static constexpr int UNCOLOURED = -1;

struct node {
	node(int v) : val{v}, colour{UNCOLOURED}
	{}

	int val;
	int colour;

	std::unordered_set<node *> neighbours;

	void add_neighbour(node *n)
	{
		neighbours.insert(n);
	}

	void add_neighbours(const std::vector<node *> ns)
	{
		for (node *n : ns) {
			add_neighbour(n);
		}
	}
};

int get_maximum_degree(node* node)
{
	if (node == nullptr)
		return 0;

	int ret = 0;

	std::unordered_set<::node *> seen;
	std::vector<::node *> to_check { node };

	while (!to_check.empty()) {
		node = to_check.back();
		to_check.pop_back();

		if (seen.find(node) != seen.end())
			continue;

		ret = std::max(ret, (int)node->neighbours.size());
		for (::node* child : node->neighbours) {
			to_check.push_back(child);
		}

		seen.insert(node);
	}

	return ret;
}

// O(N + M) time
// O(ND) storage
void colour_graph_outward(node* first, int num_colours)
{
	std::unordered_map<node *, std::unordered_set<int>> illegal_colours;
	std::unordered_set<node *> seen;
	std::deque<node *> queue { first };

	auto get_colour = [&] (node *n) -> int {
		auto& illegal_set = illegal_colours[n];
		for (int i = 0; i < num_colours; i++) {
			if (illegal_set.find(i) == illegal_set.end())
				return i;
		}

		throw std::runtime_error("Not enough colours!");
	};

	while (!queue.empty()) {
		node *curr = queue.front();
		queue.pop_front();

		if (seen.find(curr) != seen.end())
			continue;

		int colour = get_colour(curr);
		curr->colour = colour;

		for (node *neighbour : curr->neighbours) {
			illegal_colours[neighbour].insert(colour);
			queue.push_back(neighbour);
		}

		seen.insert(curr);
	}
}

// O(N + M) time
// O(N + D) storage (O(D) if we ignore queue storage).
void colour_graph(node* first, int num_colours)
{
	std::unordered_set<node *> seen;
	std::vector<node *> stack { first };

	while (!stack.empty()) {
		node *curr = stack.back();
		stack.pop_back();

		std::unordered_set<int> illegal_colours;
		for (node *neighbour : curr->neighbours) {
			if (neighbour->colour != -1)
				illegal_colours.insert(neighbour->colour);

			if (seen.find(neighbour) == seen.end())
				stack.push_back(neighbour);
		}

		for (int i = 0; i < num_colours; i++) {
			if (illegal_colours.find(i) == illegal_colours.end()) {
				curr->colour = i;
				break;
			}
		}

		seen.insert(curr);
	}
}

bool check_colours(node* first)
{
	std::unordered_set<node *> seen;
	std::deque<node *> queue { first };

	while (!queue.empty()) {
		node *curr = queue.front();
		queue.pop_front();

		if (seen.find(curr) != seen.end())
			continue;

		for (node *neighbour : curr->neighbours) {
			if (neighbour->colour == curr->colour) {
				std::cout << "node " << curr->val << " and " << neighbour->val <<
					" have same colour " << curr->colour << std::endl;

				return false;
			}
			queue.push_back(neighbour);
		}

		seen.insert(curr);
	}

	return true;
}

int main()
{
	std::vector<node *> nodes(12);
	for (int i = 1; i <= 12; i++) {
		nodes[i] = new node(i);
	}

	auto add_neighbours = [&] (int from, const std::vector<int> indexes) {
		std::vector<node *> ns;
		ns.reserve(ns.size());

		for (int index : indexes) {
			ns.push_back(nodes[index]);
		}

		nodes[from]->add_neighbours(ns);
	};

	// generate max-degree 3 graph as shown on interview cake page.
	add_neighbours(1, { 2, 3, 4 });
	add_neighbours(2, { 1, 9, 10 });
	add_neighbours(3, { 1, 11, 12 });
	add_neighbours(4, { 1, 5, 8 });
	add_neighbours(5, { 4, 6, 7 });
	add_neighbours(6, { 5, 7, 9 });
	add_neighbours(7, { 5, 6, 8 });
	add_neighbours(8, { 4, 12 });
	add_neighbours(9, { 2, 6, 10 });
	add_neighbours(10, { 2, 9, 11 });
	add_neighbours(11, { 3, 10, 12 });
	add_neighbours(12, { 3, 8, 11 });

	int max_degree = get_maximum_degree(nodes[1]);
	colour_graph(nodes[1], max_degree + 1);

	for (int i = 1; i <= 12; i++) {
		std::cout << "node " << i << " has colour " << nodes[i]->colour << std::endl;
	}

	if (!check_colours(nodes[1]))
		std::cout << "ILLEGAL COLOURING!" << std::endl;

	return 0;
}
