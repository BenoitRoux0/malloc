#include <stdio.h>

#include "test.h"

static void	remove_io(char* name);
static void put_success(char* test_name);
static void put_fail(char* test_name, int status);

int	run_test(t_test test) {
	int	ret;
	struct timeval	start;
	struct timeval	end;

	pid_t pid = fork();
	if (pid == 0) {
		remove_io(test.name);
		exit(test.func());
	}

	gettimeofday(&start, NULL);

	test_put_str(test.name);
	test_put_str(" running\r");

	waitpid(pid, &ret, 0);

	gettimeofday(&end, NULL);

	if (ret == 0) {
		put_success(test.name);
		return 0;
	}

	put_fail(test.name, ret);

	return ret;
}

static void put_success(char* test_name) {
	test_put_str("\x1b[2K");
	test_put_str(test_name);
	test_put_str(" passed\n");
}

static void put_fail(char* test_name, int status) {
	test_put_str("\x1b[2K");
	test_put_str(test_name);
	test_put_str(" failed");

	if (WIFEXITED(status)) {
		test_put_str(" with status: ");
		test_put_nbr(WEXITSTATUS(status));
	}

	if (WIFSIGNALED(status)) {
		test_put_str(" recv sig: ");
		switch (WTERMSIG(status)) {
		case SIGSEGV:
			test_put_str("sigsegv");
			break;
		default:
			test_put_nbr(WTERMSIG(status));
			break;
		}
	}

	test_put_str("\n");
}

static void	remove_io(char* name) {
	char* out_dir = getenv("TEST_OUT_DIR");

	if (out_dir == NULL || strlen(out_dir) == 0) {
		freopen("/dev/null", "a+", stdout);
		freopen("/dev/null", "a+", stderr);
	}

	chdir(out_dir);
	freopen(name, "w+", stdout);
	freopen(name, "w+", stderr);

	close(0);
}

