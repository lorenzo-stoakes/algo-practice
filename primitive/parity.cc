#include <cstdint>
#include <iostream>

static int lookup[256];

// Lookups so O(n / 8) i.e. O(n).
int parity1(uint64_t n)
{
	if (n == 0)
		return 0;

	int ret = 0;
	for (int i = 0; i < sizeof(uint64_t) / 8; i++) {
		ret ^= lookup[n & 0xff];
		n >>= 8;
	}

	return ret;
}

int parity2(uint64_t n)
{
	// The parity of 2 (bitwise) halves of an integer are equal to the
	// parity of the xor of those 2 bitwise halves.

	// O(lg n)

	n ^= (n >> 32);
	n ^= (n >> 16);
	n ^= (n >> 8);
	n ^= (n >> 4);
	n ^= (n >> 2);
	n ^= (n >> 1);

	return n & 1;
}

void init_lookup()
{
	lookup[0] = 1; // 0 is odd so parity = 1.
	for (int i = 1; i < 8; i++) {
		int n = (1 << i) - 1;

		for (int j = 0; j < 8 - i; j++) {
			lookup[n] = i % 2;
			n <<= 1;
		}
	}
}

int main()
{
	init_lookup();

	std::cout << parity2(0b0) << std::endl;
	std::cout << parity2(0b1) << std::endl;
	std::cout << parity2(0b101) << std::endl;

	std::cout << parity2(0b1111111111101010101UL) << std::endl;

	return 0;
}
