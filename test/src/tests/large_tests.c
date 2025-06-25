#include "malloc.h"
#include "test.h"

int	test_large(void) {
	void*	ptr_big = malloc(sysconf(_SC_PAGESIZE) * 2);

	free(ptr_big);

	return 0;
}

int	test_very_large(void) {
	void*	ptr_very_big = malloc(4294967296);

	free(ptr_very_big);

	return 0;
}
