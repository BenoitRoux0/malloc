#ifndef MALLOC_H
# define MALLOC_H

# include <stdbool.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdint.h>

# define TINY_MAX 16
# define TINY_ARENA_SIZE 2

# define SMALL_MAX 256
# define SMALL_ARENA_SIZE 6

enum e_types {
	TINY,
	SMALL,
	LARGE
};

typedef struct s_arena_hdr {
	bool				is_main;
	uint8_t				_[7];
	size_t				size;
	size_t				allocated;
	struct s_arena_hdr*	next;
}	t_arena_hdr;

typedef struct s_arenas {
	t_arena_hdr*	tiny;
	t_arena_hdr*	small;
	t_arena_hdr*	large;
}	t_arenas;

typedef struct s_chunk_header {
	bool		owned;
	uint32_t	offset;
	size_t		size;
}	t_chunk_header;

extern	t_arenas g_arenas;

// arenas
void*	take_tiny(size_t size);
void*	append_tiny(void);

void*	take_small(size_t size);
void*	append_small(void);

void	update_after_free_tiny(void);
void	remove_arena(t_arena_hdr** target, t_arena_hdr* to_remove);
void*	get_main(void* arena);

// utils
size_t	ft_strlen(const char* s);
void	put_str(int fd, char* s);
void	put_ptr(int fd, uintptr_t val);
void	put_hexa(int fd, size_t val);

void	end_alloc(void);

#endif // MALLOC_H
