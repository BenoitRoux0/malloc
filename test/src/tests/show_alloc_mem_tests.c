#include "test.h"
#include "malloc.h"

int	show_alloc_mem_tests(void) {
	test_put_str("before: \n");
	show_alloc_mem();

	malloc(14);
	malloc(52);
	malloc(5012);

	test_put_str("after: \n");
	show_alloc_mem();

	return 0;
}
