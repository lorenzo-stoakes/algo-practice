#include <iostream>

long fib(long n)
{
	// Negative values return garbage.
	if (n <= 1)
		return n;

	long fib_n_2 = 0;
	long fib_n_1 = 1;

	for (long i = 2; i <= n; i++) {
		long n = fib_n_1 + fib_n_2;
		fib_n_2 = fib_n_1;
		fib_n_1 = n;
	}

	return fib_n_1;
}

int main()
{
	for (long i = 0; i < 10; i++) {
		std::cout << fib(i) << std::endl;
	}

	return 0;
}
