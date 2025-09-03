#include "malloc.h"

void merge_next_chunk(t_chunk_header* chunk_hdr) {
	t_chunk_header* next_chunk = get_next_chunk(chunk_hdr);

#ifdef DEBUG

	put_str(2, "merge next chunk\n");

#endif

	if ((void*)next_chunk < get_border_addr(chunk_hdr) - sizeof(t_chunk_header)) {
		if (!next_chunk->owned) {
			chunk_hdr->true_size += next_chunk->true_size + sizeof(t_chunk_header);

			if ((void*)get_next_chunk(chunk_hdr) < get_border_addr(chunk_hdr) - sizeof(t_chunk_header)) {
				get_next_chunk(chunk_hdr)->prec_chunk = chunk_hdr;
			}
		}
	}
}