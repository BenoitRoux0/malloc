#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include "test.h"

char**	g_to_run;
bool	g_fork;

int main(int ac, char** av) {
	g_to_run = NULL;

	if (ac > 1) {
		g_to_run = &av[1];
	}

	g_fork = ac != 2;

	run_test_group("tiny tests",
		TEST(test_instant_free_tiny),
		TEST(test_free_after_tiny),
		TEST(test_100_mallocs_tiny),
		END_TESTS
	);

	run_test_group("small tests",
		TEST(test_instant_free_small),
		TEST(test_free_after_small),
		TEST(test_100_mallocs_small),
		TEST(test_10_mallocs_small),
		END_TESTS
	);

	run_test_group("large tests",
		TEST(test_large),
		TEST(test_very_large),
		END_TESTS
	);

	run_test_group("tests realloc",
		TEST(realloc_tiny2large_test),
		TEST(realloc_small2large_test),
		END_TESTS
	);

	run_test_group("tests coalescing",
		TEST(test_coalescing),
		END_TESTS
	);

	run_test_group("test show_alloc_mem",
		TEST(show_alloc_mem_tests),
		END_TESTS
	);

	return 0;
}


