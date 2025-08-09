#include <stdint.h>

#include "mtrace.h"

static void	set_sig_handler(void);

int	main(int ac, char **av) {
	(void) ac;

	pid_t			pid = fork();
	int				status = 0;

	if (pid == -1) {
		dprintf(2, "fork fail: %s\n", strerror(errno));
		return 1;
	}

	if (pid == 0) {
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		setenv("LD_PRELOAD", getenv("MALLOC_PATH"), true);
		printf("run %s\n", *(av + 1));
		int ret = execvp(*(av + 1), av + 1);
		if (ret)
			dprintf(2, "execvp error: %s\n", strerror(errno));
		exit(1);
	}

	printf("from: %d\n", getpid());
	printf("launch: %d\n", pid);

	set_sig_handler();

	bool continue_tracing = true;

	while (continue_tracing) {
		continue_tracing = false;
		waitpid(pid, &status, 0);

		if (WIFEXITED(status)) {
			dprintf(2, "exited with status: %d\n", WEXITSTATUS(status));
		}

		if (WIFSIGNALED(status)) {
			if (WTERMSIG(status) == SIGTRAP) {
				continue_tracing = true;
				ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
			}
		}

		if (WIFCONTINUED(status)) {
			dprintf(2, "continued\n");
		}

		if (WIFSTOPPED(status)) {
			if (WSTOPSIG(status) == SIGTRAP) {
				continue_tracing = true;
				ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
			}
		}
		// printf("send cont\n");
		// long int ret = kill(pid, SIGCONT);
		// if (ret != 0)
		// 	dprintf(2, "ptrace error: %s\n", strerror(errno));
	}

	return 0;
}

static void	set_sig_handler(void) {
	struct sigaction act = { 0 };

	act.sa_flags = SA_SIGINFO | SA_NODEFER;
	act.sa_sigaction = sig_handler;
//	sigaction(SIGSEGV, &act, NULL);
//	sigaction(SIGABRT, &act, NULL);
	sigaction(SIGCHLD, &act, NULL);
}
