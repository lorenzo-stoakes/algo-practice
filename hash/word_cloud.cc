#include <iostream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> get_cloud(const std::string& str)
{
	std::unordered_map<std::string, int> ret;

	size_t start = 0, end = 0;

	std::string copy = str;

	bool outside_word = false;
	char prev = '\0';
	for (size_t i = 0; i < str.size(); i++) {
		const char chr = str[i];
		switch (chr) {
		case ' ':
			if (!outside_word)
				outside_word = true;
			break;
		case '-':
			if (!outside_word)
				end = i + 1;
			break;
		case ',':
		case ';':
		case '!':
		case ':':
		case '(':
		case ')':
		case '.':
		case '\'':
			outside_word = true;
			break;
		case 's':
		case 'S':
			if (prev == '\'')
				break;

			// fallthrough
		default:
			if (outside_word) {
				std::string word(copy.begin() + start,
						 copy.begin() + end);
				ret[word]++;
				start = i;

				outside_word = false;
			}
			end = i + 1;
			copy[i] = std::tolower(chr);

			break;
		}
		prev = chr;
	}

	if (!outside_word) {
		std::string word(copy.begin() + start,
				 copy.begin() + end);
		ret[word]++;
	}

	return ret;
}

void print(const std::string& str)
{
	std::cout << "\"" << str << "\":" << std::endl;

	std::unordered_map<std::string, int> counts = get_cloud(str);

	for (auto [ str, count ] : counts) {
		std::cout << str << ": " << count << std::endl;
	}

	std::cout << std::endl;
}

int main()
{
	print("After beating the eggs, Dana read the next step:");
	print("Add milk and eggs, then add flour-sex - and sugar.");
	print("We came, we saw, we conquered...then we ate Bill's (Mille-Feuille) cake.");
	print("The bill came to five dollars.");

	return 0;
}
