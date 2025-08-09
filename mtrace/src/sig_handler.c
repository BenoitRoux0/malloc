#include <stdint.h>

#include "mtrace.h"

void	sig_handler(int signo, siginfo_t *info, void *context) {
	siginfo_t info_child;

	(void) signo;
	(void) context;

//	printf("caught: %d\n", info->si_pid);

	ptrace(PTRACE_GETSIGINFO, info->si_pid, NULL, &info_child);

	if (info_child.si_signo == SIGTRAP) {
		return;
	}

	printf("child sig: %s\n", strsignal(info->si_status));


	printf("child sig: %s\n", strsignal(info_child.si_signo));
	psiginfo(&info_child, "child");

	switch (info_child.si_code) {
	case SEGV_MAPERR:
		printf("child code: SEGV_MAPERR\n");
		break;
	case SEGV_ACCERR:
		printf("child code: SEGV_ACCERR\n");
		break;
	}

	printf("child addr: %p\n\n", info_child.si_addr);

	exit(1);
}
