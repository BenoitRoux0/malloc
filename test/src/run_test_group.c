#include "test.h"
#include "malloc.h"
#include <stdarg.h>

void	run_test_group(char* group_name, ...) {
	va_list	args;
	t_test	test;
	int		passed = 0;
	int		total = 0;

	test_put_str(group_name);
	test_put_str(": \n\n");

	va_start(args, group_name);

	test = va_arg(args, t_test);

	while (test.func != NULL) {
		if (run_test(test) == 0) {
			++passed;
		}
		test = va_arg(args, t_test);
		++total;
	}

	test_put_str("\npassed: [");
	test_put_nbr(passed);
	test_put_str("/");
	test_put_nbr(total);
	test_put_str("]\n\n");

	va_end(args);
}
