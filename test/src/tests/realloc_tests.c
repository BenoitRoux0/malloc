#include <string.h>
#include "malloc.h"
#include "test.h"

int	realloc_tiny2large_test(void) {
	char	data[] = "Hello world";
	char*	ptr = malloc(15);

	memcpy(ptr, data, 11);

	char* new_ptr = realloc(ptr, 4096);

	if (memcmp(new_ptr, data, sizeof(data)) != 0) {
		free(new_ptr);
		free(ptr);
		return 1;
	}

	free(new_ptr);
	free(ptr);

	return 0;
}

int	realloc_small2large_test(void) {
	char	data[] = "Hello world";
	char*	ptr = malloc(32);

	memcpy(ptr, data, 11);

	char* reallocated_ptr = realloc(ptr, 4096);

	if (memcmp(reallocated_ptr, data, sizeof(data)) != 0) {
		free(reallocated_ptr);
		free(ptr);
		return 1;
	}

	free(reallocated_ptr);
	free(ptr);

	char*	new_ptr = malloc(64);

	free(new_ptr);

	if (ptr != new_ptr)
		return 2;

	return 0;
}
