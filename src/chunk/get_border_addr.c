#include "malloc.h"

void*   get_border_addr(t_chunk_header* chunk) {
    void*   arena = get_main_arena(chunk);

    return arena + has_arena(arena)->size;
}
