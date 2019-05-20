#include <sys/mman.h>
#include <dirent.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	char *file_name = argv[1];
	int fd = open(file_name, O_RDONLY);
	if (fd == -1) return 0;
	struct stat st;
	fstat(fd, &st);
	if (st.st_size == 0) return 0;
	int *contents = mmap(NULL,
			st.st_size,
			PROT_READ,
			MAP_SHARED,
			fd,
			0);
	int value = contents[0];
	uint32_t new_pointer = contents[1];
	printf("%d\n", value);
	while (new_pointer > 0) {
		value = contents[new_pointer / 4];
		new_pointer = contents[new_pointer / 4 + 1];
		printf("%d\n", value);
	}
	munmap(contents, st.st_size);
	close(fd);
	return 0;
}
