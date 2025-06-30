#include "test.h"
#include "malloc.h"

static bool	must_run(char* test_name);

void	run_test_group(char* group_name, ...) {
	va_list	args;
	t_test	test;
	int		passed = 0;
	int		total = 0;
	int		ignored = 0;

	va_start(args, group_name);
	test = va_arg(args, t_test);

	test_put_str(group_name);

	while (test.func != NULL) {
		if (must_run(test.name)) {
			if (total == 0) {
				test_put_str(":\n\n");
			}
			if (run_test(test) == 0) {
				++passed;
			}
			++total;
		} else {
			++ignored;
		}
		test = va_arg(args, t_test);
	}

	if (total == 0) {
		test_put_str(": all ignored\n");
		return;
	}

	test_put_str("\npassed: [");
	test_put_nbr(passed);
	test_put_str("/");
	test_put_nbr(total);
	test_put_str("] ");
	if (ignored != 0) {
		test_put_str("(");
		test_put_nbr(ignored);
		test_put_str(" ignored");
		test_put_str(")");
	}
	test_put_str("\n\n");

	va_end(args);
}

static bool	must_run(char* test_name) {
	if (g_to_run == NULL) {
		return true;
	}

	for (size_t i = 0; g_to_run[i]; ++i) {
		if (strcmp(test_name, g_to_run[i]) == 0) {
			return true;
		}
	}

	return false;
}
