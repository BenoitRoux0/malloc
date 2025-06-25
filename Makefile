ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc.so
FULL_NAME = libft_malloc_$(HOSTTYPE).so
FT_TEST_NAME = libft_malloc_test
TEST_NAME = malloc_test

SRC =	src/free/free.c \
		src/malloc/malloc.c \
		src/realloc/realloc.c \
		src/utils/str.c \
		src/utils/puts.c \
		src/arena/append_tiny.c \
		src/arena/append_small.c \
		src/arena/take_tiny.c \
		src/arena/take_small.c \
		src/arena/update_after_free.c \
		src/arena/get_main.c \
		src/chunk/get_chunk_size.c \
		src/chunk/get_next_page.c \
		src/chunk/get_next_chunk.c \
		src/end_alloc.c \

SRC_TEST =	test/main.c \

OBJ_DIR = .objs

OBJ =		$(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_TEST =	$(SRC_TEST:%.c=$(OBJ_DIR)/%.o)

CFLAGS =		-Wall -Wextra -Werror -g3 -fpic
CFLAGS_TEST =	-Wall -Wextra -Werror -g3

all:	test

test:	$(TEST_NAME) $(FT_TEST_NAME)

run_test:	test
			@mkdir -p .test_out/
			@echo "running tests for libft_malloc"
			@/usr/bin/time --format='major: %F\nminor: %R' --output=.test_out/ft_out ./libft_malloc_test
			@echo "running tests for true_malloc"
			@/usr/bin/time --format='major: %F\nminor: %R' --output=.test_out/true_out ./malloc_test
			@diff .test_out/ft_out .test_out/true_out

$(OBJ_DIR)/src/%.o:		src/%.c	include/internal/malloc.h
						@mkdir -p $(shell dirname $@)
						$(CC) $(CFLAGS) -o $@ -c $< -Iinclude/internal

$(OBJ_DIR)/test/%.o:	test/%.c include/public/malloc.h
						@mkdir -p $(shell dirname $@)
						$(CC) $(CFLAGS_TEST) -o $@ -c $< -Iinclude/public

$(NAME):				$(FULL_NAME)
						@ln -s $(FULL_NAME) $(NAME) 2> /dev/null && echo "link created" || echo "link already exists"

$(FULL_NAME):			$(OBJ)
						$(CC) -shared -Wl,-fini=end_alloc -o $@ $^

$(FT_TEST_NAME):		$(NAME) $(OBJ_TEST)
						$(CC) -L. -Wl,-rpath=. -o $@ $(OBJ_TEST) -lft_malloc

$(TEST_NAME):			$(NAME) $(OBJ_TEST)
						$(CC) -o $@ $(OBJ_TEST)

clean:
						$(RM) -r $(OBJ_DIR)

fclean:					clean
						$(RM) $(NAME)
						$(RM) $(FULL_NAME)
						$(RM) $(TEST_NAME)
						$(RM) $(FT_TEST_NAME)

re:						fclean
						$(MAKE) all
