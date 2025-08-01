#include "malloc.h"
#include "test.h"

int	test_instant_free_small(void) {
	char	data[] = "Hello world";

	for (int i = 0; i < 200; ++i) {
		void*	ptr = malloc(1024);

		memcpy(ptr, data, 11);

		if (memcmp(ptr, data, sizeof(data)) != 0) {
			return 1;
		}

		free(ptr);
	}

	return 0;
}

int	test_free_after_small(void) {
	void*	ptrs_1[4096];
	void*	ptrs_2[4096];
	void*	ptrs_3[4096];

	for (int i = 0; i < 4096; ++i) {
		ptrs_1[i] = malloc(32);

		bzero(ptrs_1[i], 32);

		ptrs_2[i] = malloc(256);

		bzero(ptrs_2[i], 256);

		ptrs_3[i] = malloc(128);

		bzero(ptrs_3[i], 128);
	}

	for (int i = 0; i < 4096; ++i) {
		free(ptrs_1[i]);
		free(ptrs_2[i]);
		free(ptrs_3[i]);
	}

	return 0;
}

int	test_10_mallocs_small(void) {
	char	data[] = "Hello world";
	void*	ptrs[10];

	for (int i = 0; i < 10; ++i) {
		ptrs[i] = malloc(1024);

		memcpy(ptrs[i], data, 11);
		if (memcmp(ptrs[i], data, sizeof(data)) != 0) {
			return 1;
		}
	}

	t_malloc_data malloc_data = get_malloc_data();

	for (int i = 0; i < 10; ++i) {
		// free(ptrs[i]);
	}

	if (malloc_data.mmaped_small != 1)
		return malloc_data.mmaped_small;

	return 0;
}

int	test_100_mallocs_small(void) {
	char	data[] = "Hello world";
	void*	ptrs[100];

	for (int i = 0; i < 100; ++i) {
		ptrs[i] = malloc(1024);

		memcpy(ptrs[i], data, 11);
		if (memcmp(ptrs[i], data, sizeof(data)) != 0) {
			return 1;
		}
	}

	t_malloc_data malloc_data = get_malloc_data();

	for (int i = 0; i < 100; ++i) {
		// free(ptrs[i]);
	}

	if (malloc_data.mmaped_small != 1)
		return malloc_data.mmaped_small;

	return 0;
}
