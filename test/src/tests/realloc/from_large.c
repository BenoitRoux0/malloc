#include <string.h>
#include "malloc.h"
#include "test.h"

int	realloc_large2larger_large_test(void) {
	char	data[] = "Hello world";
	void*	ptr = malloc(2048);

	if (!ptr)
		return 1;

	memcpy(ptr, data, 11);

	void*	ptr_ext = realloc(ptr, 4096);

	if (!ptr_ext) {
		free(ptr);
		return 2;
	}

	if (memcmp(ptr_ext, data, 11) != 0) {
		free(ptr_ext);
		free(ptr);
		return 3;
	}

	return 0;
}

int	realloc_larger_large2large_test(void) {
	char	data[] = "Hello world";
	void*	ptr = malloc(4096);

	if (!ptr)
		return 1;

	memcpy(ptr, data, 11);

	void*	ptr_ext = realloc(ptr, 2048);

	if (!ptr_ext) {
		free(ptr);
		return 2;
	}

	if (memcmp(ptr_ext, data, 11) != 0) {
		free(ptr_ext);
		free(ptr);
		return 3;
	}

	free(ptr_ext);

	if (ptr_ext != ptr) {
		return 3;
	}

	return 0;
}

int	realloc_large2tiny_test(void) {
	char	data[] = "Hello world";
	void*	ptr = malloc(4096);

	if (!ptr)
		return 1;

	memcpy(ptr, data, 11);

	void*	ptr_ext = realloc(ptr, 15);

	if (!ptr_ext) {
		free(ptr);
		return 2;
	}

	if (memcmp(ptr_ext, data, 11) != 0) {
		free(ptr_ext);
		free(ptr);
		return 3;
	}

	free(ptr_ext);

	return 0;
}

int	realloc_large2small_test(void) {
	char	data[] = "Hello world";
	void*	ptr = malloc(4096);

	if (!ptr)
		return 1;

	memcpy(ptr, data, 11);

	void*	ptr_ext = realloc(ptr, 64);

	if (!ptr_ext) {
		free(ptr);
		return 2;
	}

	if (memcmp(ptr_ext, data, 11) != 0) {
		free(ptr_ext);
		return 3;
	}

	free(ptr_ext);

	return 0;
}
