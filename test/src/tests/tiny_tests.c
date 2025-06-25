#include "test.h"
#include "malloc.h"

int	test_instant_free_tiny(void) {
	char	data[] = "Hello world";

	for (int i = 0; i < 200; ++i) {
		void*	ptr = malloc(14);
		memcpy(ptr, data, 11);
		if (memcmp(ptr, data, sizeof(data)) != 0) {
			return 1;
		}
		free(ptr);
	}

	return 0;
}

int	test_free_after_tiny(void) {
	char	data[] = "Hello world";
	void*	ptrs[500];

	for (int i = 0; i < 500; ++i) {
		ptrs[i] = malloc(14);
		memcpy(ptrs[i], data, 11);
		if (memcmp(ptrs[i], data, sizeof(data)) != 0) {
			return 1;
		}
	}

	for (int i = 0; i < 500; ++i) {
		free(ptrs[i]);
	}

	return 0;
}
