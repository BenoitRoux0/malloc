#include "test.h"

static void	redirect_io(char* name);
static void put_success(char* test_name);
static void put_fail(char* test_name, int status);
static void put_time_diff(struct timeval diff);

int	run_test(t_test test) {
	int				status;
	struct timeval	start;
	struct timeval	end;
	struct timeval	diff;

	pid_t pid = fork();
	if (pid == 0) {
		redirect_io(test.name);
		exit(test.func());
	}

	gettimeofday(&start, NULL);

	test_put_str(test.name);
	test_put_str(" running\r");

	waitpid(pid, &status, 0);

	gettimeofday(&end, NULL);

	timersub(&end, &start, &diff);

	if (status == 0) {
		put_success(test.name);
	} else {
		put_fail(test.name, status);
	}

	put_time_diff(diff);
	return status;
}

static void put_time_diff(struct timeval diff) {
	long ms = diff.tv_usec / 1000;

	test_put_str(" ");
	test_put_nbr(ms);
	test_put_str(".");
	test_put_nbr(diff.tv_usec - ms);
	test_put_str(" ms\n");
}

static void put_success(char* test_name) {
	test_put_str("\x1b[2K");
	test_put_str(test_name);
	test_put_str(" passed");
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
}

static void	redirect_io(char* name) {
	char* out_dir = getenv("TEST_OUT_DIR");

	if (out_dir == NULL || strlen(out_dir) == 0) {
		freopen("/dev/null", "a+", stdout);
		freopen("/dev/null", "a+", stderr);
		return;
	}

	chdir(out_dir);
	freopen(name, "w+", stdout);
	freopen(name, "w+", stderr);

	close(0);
}

