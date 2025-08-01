#include "malloc.h"

void	unlock_alloc(void) {
#ifdef BONUS
# ifdef DEBUG
	put_str(2, "unlock alloc\n");
# endif
	pthread_mutex_unlock(&g_alloc_mutex);
# ifdef DEBUG
	put_str(2, "alloc unlocked\n");
# endif
#endif
}
