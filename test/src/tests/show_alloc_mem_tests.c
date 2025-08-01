#include "test.h"
#include "malloc.h"

# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-result"

int	show_alloc_mem_tests(void) {
	test_put_str("before: \n");
	show_alloc_mem();

	malloc(14);
	malloc(13);
	malloc(15);
	malloc(8);
	malloc(52);
	malloc(5012);
	malloc(4096);

	test_put_str("after: \n");
	show_alloc_mem();

	return 0;
}

# pragma GCC diagnostic pop
