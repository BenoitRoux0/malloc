#include "malloc.h"
#include "test.h"

int	test_coalescing(void) {
	void *ptr_1 = malloc(32);
	void *ptr_2 = malloc(32);
	void *ptr_3 = malloc(32);

	free(ptr_1);
	free(ptr_2);

	void *new_ptr = malloc(64);

	free(new_ptr);
	free(ptr_3);

	if (ptr_1 == new_ptr)
		return 0;

	return 1;
}
