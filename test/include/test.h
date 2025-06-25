#ifndef TEST_H
# define TEST_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/time.h>

typedef int	(*test_func)(void);

typedef struct
{
	char*		name;
	test_func	func;
}	t_test;

# define TEST(f) ((t_test) {#f, f})

int		run_test(t_test test);
void	run_test_group(char* group_name, ...);

int	test_instant_free_tiny(void);
int	test_free_after_tiny(void);
int	test_instant_free_small(void);
int	test_free_after_small(void);
int	test_large(void);
int	test_very_large(void);
int	show_alloc_mem_tests(void);

void	test_put_str(char* s);
void	test_put_nbr(int n);

#endif
