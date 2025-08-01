#include "malloc.h"

void	lock_alloc(void) {
#ifdef BONUS
# ifdef DEBUG
	put_str(2, "lock alloc\n");
# endif
	pthread_mutex_lock(&g_alloc_mutex);
# ifdef DEBUG
	put_str(2, "alloc locked\n");
# endif
#endif
}
