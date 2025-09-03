#include <string.h>
#include "malloc.h"
#include "test.h"

int	realloc_small2larger_small_test(void) {
	char	data[] = "Hello world";
	void*	ptr_1 = malloc(32);
	void*	ptr_2 = malloc(32);
	void*	ptr_3 = malloc(32);

	memcpy(ptr_1, data, 11);

	free(ptr_2);

	void*	ptr_1_ext = realloc(ptr_1, 64);

	if (!ptr_1_ext) {
		free(ptr_1);
		free(ptr_3);
		return 1;
	}

	if (memcmp(ptr_1_ext, data, 11) != 0) {
		free(ptr_1_ext);
		free(ptr_3);
		return 1;
	}

	free(ptr_1_ext);

	if (ptr_1 != ptr_1_ext)
		return 2;

	return 0;
}

int	realloc_larger_small2small_test(void) {
	char	data[] = "Hello world";
	void*	ptr_1 = malloc(64);
	void*	ptr_2 = malloc(32);

	memcpy(ptr_1, data, 11);

	free(ptr_2);

	void*	ptr_1_ext = realloc(ptr_1, 32);

	if (!ptr_1_ext) {
		free(ptr_1);
		return 1;
	}

	if (memcmp(ptr_1_ext, data, 11) != 0) {
		free(ptr_1_ext);
		return 1;
	}

	free(ptr_1_ext);

	if (ptr_1 != ptr_1_ext)
		return 2;

	return 0;
}

int	realloc_small2tiny_test(void) {
	char	data[] = "Hello world";
	char*	ptr = malloc(32);

	memcpy(ptr, data, 11);

	char* reallocated_ptr = realloc(ptr, 15);

	if (memcmp(reallocated_ptr, data, 11) != 0) {
		free(reallocated_ptr);
		free(ptr);
		return 1;
	}

	free(reallocated_ptr);
	free(ptr);

	char*	new_ptr = malloc(64);

	free(new_ptr);

	if (strncmp(ptr, new_ptr, 11) != 0)
		return 2;

	return 0;
}

int	realloc_small2large_test(void) {
	char	data[] = "Hello world";
	char*	ptr = malloc(32);

	memcpy(ptr, data, 11);

	char* reallocated_ptr = realloc(ptr, 4096);

	if (!reallocated_ptr) {
		free(ptr);
		return 1;
	}

	if (memcmp(reallocated_ptr, data, 11) != 0) {
		free(reallocated_ptr);
		free(ptr);
		return 1;
	}

	free(reallocated_ptr);

	char*	new_ptr = malloc(64);

	if (strncmp(ptr, new_ptr, 11) != 0) {
		free(ptr);
		free(new_ptr);
		return 2;
	}

	free(ptr);
	free(new_ptr);


	return 0;
}
