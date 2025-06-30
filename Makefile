ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc.so
FULL_NAME = libft_malloc_$(HOSTTYPE).so
FT_TEST_NAME = libft_malloc_test
TEST_NAME = malloc_test
MOCKS_NAME = mocks.a

CC = gcc

SRC =	src/free/free.c \
		src/malloc/malloc.c \
		src/realloc/realloc.c \
		src/show_alloc_mem/show_alloc_mem.c \
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
		src/chunk/get_main_arena.c \
		src/end_alloc.c \

SRC_TEST =	test/src/main.c \
			test/src/run_test.c \
			test/src/run_test_group.c \
			test/src/test_utils.c \
			test/src/tests/tiny_tests.c \
			test/src/tests/small_tests.c \
			test/src/tests/large_tests.c \
			test/src/tests/show_alloc_mem_tests.c \

SRC_MOCKS = test/src/mocks/show_alloc_mem.c

OBJ_DIR = .objs

OBJ =		$(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_TEST =	$(SRC_TEST:%.c=$(OBJ_DIR)/%.o)
OBJ_MOCKS =	$(SRC_MOCKS:%.c=$(OBJ_DIR)/%.o)

CFLAGS =		-Wall -Wextra -Werror -fpic
CFLAGS_TEST =	-Wall -Wextra -Werror -funroll-loops

all:	test

test:	$(FT_TEST_NAME) $(TEST_NAME)

run_test:	test
			@mkdir -p .ft_test_out/
			@mkdir -p .test_out/
			@echo "running tests for libft_malloc"
			@TEST_OUT_DIR=./.ft_test_out/ /usr/bin/time --format='major: %F\nminor: %R' --output=.ft_test_out/faults ./libft_malloc_test
			@echo "running tests for true_malloc"
			@TEST_OUT_DIR=./.test_out/ /usr/bin/time --format='major: %F\nminor: %R' --output=.test_out/faults ./malloc_test
			@diff .ft_test_out/faults .test_out/faults

$(OBJ_DIR)/src/%.o:		src/%.c	include/internal/malloc.h
						@mkdir -p $(shell dirname $@)
						$(CC) $(CFLAGS) -o $@ -c $< -Iinclude/internal

$(OBJ_DIR)/test/src/%.o:	test/src/%.c include/public/malloc.h test/include/test.h
							@mkdir -p $(shell dirname $@)
							$(CC) $(CFLAGS_TEST) -o $@ -c $< -Iinclude/public -Itest/include

$(NAME):				$(FULL_NAME)
						@ln -s $(FULL_NAME) $(NAME) 2> /dev/null && echo "link created" || echo "link already exists"

$(FULL_NAME):			$(OBJ)
						$(CC) -shared -o $@ $^

$(FT_TEST_NAME):		$(NAME) $(OBJ_TEST)
						$(CC) -L. -Wl,-rpath=. -o $@ $(OBJ_TEST) -lft_malloc

$(MOCKS_NAME):			$(OBJ_MOCKS)
						ar -rc $@ $(OBJ_MOCKS)

$(TEST_NAME):			$(OBJ_TEST) $(MOCKS_NAME)
						$(CC) -o $@ $(OBJ_TEST) $(MOCKS_NAME)

clean:
						$(RM) -r $(OBJ_DIR)

fclean:					clean
						$(RM) $(NAME)
						$(RM) $(FULL_NAME)
						$(RM) $(TEST_NAME)
						$(RM) $(FT_TEST_NAME)
						$(RM) $(MOCKS_NAME)

re:						fclean
						$(MAKE) all
