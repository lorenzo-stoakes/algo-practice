#include <cstdint>
#include <iostream>

int count_bits(uint64_t n)
{
	int ret = 0;
	while (n > 0) {
		if (n & 1)
			ret++;
		n >>= 1;
	}
	return ret;
}

int main()
{
	std::cout << count_bits(0b11101) << std::endl;
}
