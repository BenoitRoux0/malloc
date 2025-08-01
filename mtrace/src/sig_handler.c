#include <stdint.h>

#include "mtrace.h"

void	sig_handler(int signo, siginfo_t *info, void *context) {
	(void) context;

	printf("sig: %s\n", strsignal(signo));

	switch (info->si_code) {
	case SEGV_MAPERR:
		printf("code: SEGV_MAPERR\n");
		break;
	case SEGV_ACCERR:
		printf("code: SEGV_ACCERR\n");
		break;
	}

	printf("addr: %p\n", info->si_addr);
	printf("lsb: %x\n", info->si_addr_lsb);

//	if (sigaction(SIGSEGV, NULL, &oldact) == -1) {
//		_exit(EXIT_FAILURE);
//	}

	show_alloc_mem();
}
