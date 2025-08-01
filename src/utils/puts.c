#include "malloc.h"

ssize_t put_str(int fd, char* str) {
	return write(fd, str, ft_strlen(str));
}

void put_ptr(int fd, uintptr_t ptr) {
	put_str(fd, "0x");
	put_hexa(fd, ptr);
}

ssize_t put_hexa(int fd, size_t val) {
	char	to_print;
	ssize_t	count = 0;

	if (val > 15)
		count = put_hexa(fd, val / 16);
	to_print = val % 16;
	if (to_print <= 9)
		to_print += 48;
	else
		to_print += 55;
	return count + write(fd, &to_print, 1);
}

ssize_t put_nbr(int fd, size_t val) {
	char	to_print;
	ssize_t	count = 0;

	if (val > 9)
		count = put_nbr(fd, val / 10);

	to_print = val % 10 + '0';

	return count + write(fd, &to_print, 1);
}
