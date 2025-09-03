#include <strings.h>

#include "malloc.h"

void*	alloc_small(size_t size, t_chunk_header* hint) {
#ifdef DEBUG
	put_str(2, "alloc small: ");
	put_nbr(2, size);
	put_str(2, "\n");
	if (hint) {
		put_str(2, "hint: ");
		put_ptr(2, (uintptr_t) hint);
		put_str(2, "\n");
	}
#endif
	lock_alloc();

	void*	ptr = take_small(size, hint);
//	put_str(1, "small alloc'd\n");

//	bzero(ptr + sizeof (t_chunk_header), size);

#ifdef DEBUG
	if (is_out(ptr)) {
		put_str(2, "alloc small addr out: ");
		put_ptr(2, (uintptr_t) ptr);
		put_str(2, "\n");
	}
#endif

	unlock_alloc();

	if (ptr == NULL)
		return NULL;


	return ptr + sizeof (t_chunk_header);
}
