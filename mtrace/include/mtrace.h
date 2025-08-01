#ifndef MTRACE_H
# define MTRACE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <wait.h>
# include <signal.h>
# include "malloc.h"

void	sig_handler(int signo, siginfo_t *info, void *context);

#endif
