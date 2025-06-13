#include "malloc.h"

size_t	ft_strlen(const char* s) {
	size_t i = 0;

	for (; s[i] ; ++i);

	return i;
}
