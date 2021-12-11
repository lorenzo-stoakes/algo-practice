// See https://www.interviewcake.com/question/cpp/mesh-message?course=fc1&section=trees-graphs

#include <algorithm>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using mesh_t = std::unordered_map<std::string, std::vector<std::string>>;

std::vector<std::string> backtrack(const std::unordered_map<std::string, std::string>& linkage,
				   const std::string& from,
				   const std::string& to)
{
	std::vector<std::string> ret { to };

	if (from == to)
		return ret;

	std::string name = linkage.find(to)->second;
	while (name != from) {
		ret.push_back(name);
		name = linkage.find(name)->second;
	}
	ret.push_back(from);

	std::reverse(ret.begin(), ret.end());

	return ret;
}

std::vector<std::string> find_shortest_path(const mesh_t& mesh,
					    const std::string& from,
					    const std::string& to)
{
	if (mesh.find(from) == mesh.end())
		throw std::runtime_error(from + " not found! (1)");

	std::deque<std::string> queue { from };
	std::unordered_map<std::string, std::string> linkage;

	while (!queue.empty()) {
		std::string name = std::move(queue.front());
		queue.pop_front();

		if (name == to)
			return backtrack(linkage, from, to);

		if (mesh.find(name) == mesh.end())
			throw std::runtime_error(name + " not found! (2)");

		for (const std::string& connection : mesh.find(name)->second) {
			if (linkage.count(connection) == 0) {
				linkage[connection] = name;
				queue.push_back(connection);
			}
		}
	}

	throw std::runtime_error(to + " not found! (3)");
}

int main()
{
	mesh_t mesh {
		{ "Min",     { "William", "Jayden", "Omar" } },
		{ "William", { "Min", "Noam" } },
		{ "Jayden",  { "Min", "Amelia", "Ren", "Noam" } },
		{ "Ren",     { "Jayden", "Omar" } },
		{ "Amelia",  { "Jayden", "Adam", "Miguel" } },
		{ "Adam",    { "Amelia", "Miguel", "Sofia", "Lucas" } },
		{ "Miguel",  { "Amelia", "Adam", "Liam", "Nathan" } },
		{ "Noam",    { "Nathan", "Jayden", "William" } },
		{ "Omar",    { "Ren", "Min", "Scott" } },
		{ "Nathan",  { "Miguel", "Noam" } },
		{ "Scott",  { "Omar" } },
	};

	for (const std::string& name : find_shortest_path(mesh, "Jayden", "Jayden")) {
		std::cout << name << std::endl;
	}

	std::cout << "---" << std::endl;

	for (const std::string& name : find_shortest_path(mesh, "Jayden", "Adam")) {
		std::cout << name << std::endl;
	}

	std::cout << "---" << std::endl;

	for (const std::string& name : find_shortest_path(mesh, "Min", "Adam")) {
		std::cout << name << std::endl;
	}

	return 0;
}
