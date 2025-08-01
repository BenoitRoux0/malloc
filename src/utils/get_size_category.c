#include "malloc.h"

t_size_category	get_size_category(size_t size) {
	if (size <= TINY_MAX)
		return TINY;

	if (size <= SMALL_MAX)
		return SMALL;

	return LARGE;
}
