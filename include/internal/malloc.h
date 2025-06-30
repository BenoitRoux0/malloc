#ifndef MALLOC_H
# define MALLOC_H

# include <stdbool.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdint.h>
# include <string.h>

# define TINY_MAX 16
# define TINY_ARENA_SIZE 16

# define SMALL_MAX 1024
# define SMALL_ARENA_SIZE 64

# define has_chunk(ptr) ((t_chunk_header*) ptr)
# define has_arena(ptr) ((t_arena_hdr*) ptr)

enum e_types {
	TINY,
	SMALL,
	LARGE
};

typedef struct s_arena_hdr {
	bool				is_main;
	uint8_t				_[6];
	size_t				size;
	size_t				allocated;
	struct s_arena_hdr*	next;
}	t_arena_hdr;

typedef struct s_arenas {
	long int		page_size;
	long int		tiny_arena_size;
	t_arena_hdr*	tiny;
	long int		small_arena_size;
	t_arena_hdr*	small;
	t_arena_hdr*	large;
}	t_arenas;

typedef struct s_chunk_header {
	size_t		prec_size;
	bool		owned;
	uint8_t		_[8];
	// size_t		offset;
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

// chunks
size_t			get_chunk_size(const void* chunk);
void*			get_next_page(void* chunk);
void*			get_next_chunk(void* chunk);
t_arena_hdr*	get_main_arena(void* chunk);

// utils
size_t	ft_strlen(const char* s);
ssize_t	put_str(int fd, char* s);
void	put_ptr(int fd, uintptr_t val);
ssize_t	put_hexa(int fd, size_t val);

void	end_alloc(void);

#endif // MALLOC_H
