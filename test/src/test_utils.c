#include "test.h"

void	test_put_str(char* s) {
	write(1, s, strlen(s));
}

void	test_put_nbr(int n) {
	char	to_write;

	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(1, "-", 1);
			n *= -1;
		}
		to_write = n % 10 + 48;
		if (n > 9)
			test_put_nbr(n / 10);
		write(1, &to_write, 1);
	}
}
