#include <stdlib.h>
#include <execinfo.h>
#define __USE_GNU
#include <dlfcn.h>
#include <strings.h>

#include "stdio.h"
#include "malloc.h"

int	test_printf(void) {
	printf("Hello: %d\n", 42);

	return 0;
}

static void	test_backtrace_inner(void);
static void	test_backtrace_inner_inner(void);

int	test_backtrace(void) {
	test_backtrace_inner();

	return 0;
}

static void	test_backtrace_inner(void) {
	test_backtrace_inner_inner();
}

static void	test_backtrace_inner_inner(void) {
	void *array[10];
	int size;
	Dl_info	info;

	size = backtrace (array, 10);
	bzero(&info, sizeof (Dl_info));
	for (int i = 0; i < size; ++i) {
		dladdr(array[i], &info);
		if (info.dli_fname)
			printf("shared object: %s\n", info.dli_fname);
		if (info.dli_sname)
			printf("symbol: %s\n", info.dli_sname);
	}
	backtrace_symbols_fd(array, size, 1);
}
