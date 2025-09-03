#include <string.h>
#include "malloc.h"
#include "test.h"

int	realloc_tiny2larger_tiny_test(void) {
	void*	ptr = malloc(12);

	void*	ptr_ext = realloc(ptr, 15);

	if (!ptr_ext) {
		free(ptr);
		return 1;
	}

	free(ptr_ext);

	if (ptr != ptr_ext) {
		return 2;
	}

	return 0;
}

int	realloc_larger_tiny2tiny_test(void) {
	void*	ptr = malloc(15);

	void*	ptr_ext = realloc(ptr, 12);

	if (!ptr_ext) {
		free(ptr);
		return 1;
	}

	free(ptr_ext);

	if (ptr != ptr_ext) {
		return 2;
	}

	return 0;
}

int	realloc_tiny2small_test(void) {
	char	data[] = "Hello world";
	char*	ptr = malloc(15);

	memcpy(ptr, data, 11);

	char* new_ptr = realloc(ptr, 32);

	if (memcmp(new_ptr, data, 11) != 0) {
		free(new_ptr);
		free(ptr);
		return 1;
	}

	free(new_ptr);
	free(ptr);

	return 0;
}

int	realloc_tiny2large_test(void) {
	char	data[] = "Hello world";
	char*	ptr = malloc(15);

	memcpy(ptr, data, 11);

	char* new_ptr = realloc(ptr, 4096);

	if (memcmp(new_ptr, data, 11) != 0) {
		free(new_ptr);
		free(ptr);
		return 1;
	}

	free(new_ptr);

	return 0;
}
