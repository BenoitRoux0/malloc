#ifndef TEST_H
# define TEST_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>
# include <sys/resource.h>

typedef int	(*test_func)(void);

typedef struct
{
	char*		name;
	test_func	func;
}	t_test;

# define TEST(f) ((t_test) {#f, f})
# define END_TESTS ((t_test) {NULL, NULL})

int		run_test(t_test test);
void	run_test_group(char* group_name, ...);

int	test_instant_free_tiny(void);
int	test_free_after_tiny(void);
int	test_100_mallocs_tiny(void);

int	test_instant_free_small(void);
int	test_free_after_small(void);
int	test_100_mallocs_small(void);
int	test_10_mallocs_small(void);

int	test_large(void);
int	test_very_large(void);
int	show_alloc_mem_tests(void);

int	test_coalescing(void);

void	test_put_str(char* s);
void	test_put_nbr(int n);

int	realloc_tiny2larger_tiny_test(void);
int	realloc_larger_tiny2tiny_test(void);
int	realloc_tiny2small_test(void);
int	realloc_tiny2large_test(void);

int	realloc_small2larger_small_test(void);
int	realloc_larger_small2small_test(void);
int	realloc_small2tiny_test(void);
int	realloc_small2large_test(void);

int	realloc_large2larger_large_test(void);
int	realloc_larger_large2large_test(void);
int	realloc_large2tiny_test(void);
int	realloc_large2small_test(void);

int	test_printf(void);

extern char**	g_to_run;
extern bool		g_fork;


#endif
