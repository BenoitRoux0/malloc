#include <strings.h>

#include "malloc.h"

void*	alloc_tiny(size_t size) {
#ifdef DEBUG
 	put_str(2, "alloc tiny\n");
#endif

	lock_alloc();

	void*	ptr = take_tiny(size);

	if (ptr != NULL)
		bzero(ptr + sizeof (t_chunk_header), size);

#ifdef DEBUG
 	put_str(2, "tiny alloc'd\n");
#endif

	unlock_alloc();

	if (ptr == NULL)
		return NULL;

	return ptr + sizeof (t_chunk_header);
}
