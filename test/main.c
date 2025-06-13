#include <malloc.h>
#include <string.h>
#include <unistd.h>

int main(void) {
	char	data[] = "Hello world";
	void*	ptrs[500];

	for (int i = 0; i < 200; ++i) {
		void*	ptr = malloc(14);
		memcpy(ptr, data, 11);
		free(ptr);
	}

	for (int i = 0; i < 500; ++i) {
		ptrs[i] = malloc(14);
		memcpy(ptrs[i], data, 11);
	}

	for (int i = 0; i < 500; ++i) {
		free(ptrs[i]);
	}

	void*	ptr_big = malloc(sysconf(_SC_PAGESIZE) * 2);

	free(ptr_big);

	return 0;
}
