#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include "test.h"

int main(void) {
	run_test_group("tiny tests",
		TEST(test_instant_free_tiny),
		TEST(test_free_after_tiny),
		TEST(NULL)
	);

	run_test_group("small tests",
		TEST(test_instant_free_small),
		TEST(test_free_after_small),
		TEST(NULL)
	);

	run_test_group("large tests",
		TEST(test_large),
		TEST(test_very_large),
		TEST(NULL)
	);

	run_test_group("test show_alloc_mem",
		TEST(show_alloc_mem_tests),
		TEST(NULL)
	);

	return 0;
}


