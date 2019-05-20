#include <sys/mman.h>
#include <dirent.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void fill_frame(uint32_t W, uint32_t N, uint32_t n, uint32_t offset, uint32_t x, char* data) {
	if (n == 1) {
		char * num = data + W * (N * offset + offset) + offset;
		char a = num[W];
		sprintf(num, "%*d", W, x);
		num[W] = a;
	}
	else if (n == 2) {
		char * num = data + W * (N * offset + offset) + offset;
		char a = num[W];
		sprintf(num, "%*d", W, x);
		num[W] = a;
		num = data + W * (N * offset + (offset + 1)) + offset;
		a = num[W];
		sprintf(num, "%*d", W, x + 1);
		num[W] = a;
		num = data + W * (N * (offset + 1) + offset) + 1 + offset;
		a = num[W];
		sprintf(num, "%*d", W, x + 3);
		num[W] = a;
		num = data + W * (N * (offset + 1) + offset + 1) + 1 + offset;
		a = num[W];
		sprintf(num, "%*d", W, x + 2);
		num[W] = a;
	}
	else {
		char *num;
		for (int i = 0; i < n; i++) {
			num = data + W * (N * offset + offset + i) + offset;
			char a = num[W];
			sprintf(num, "%*d", W, x + i);
			num[W] = a;
		}
		for (int i = 0; i < n; i++) {
			num = data + W * (N * (offset + n - 1) + offset + i) + n - 1 + offset;
			char a = num[W];
			sprintf(num, "%*d", W, x + 3 * (n - 1) - i);
			num[W] = a;
		}
		for (int i = 0; i < n - 2; i++) {
			num = data + W * (N * (offset + 1 + i) + offset + n - 1) + 1 + i + offset;
			char a = num[W];
			sprintf(num, "%*d", W, x + n + i);
			num[W] = a;
		}
		for (int i = 0; i < n - 2; i++) {
			num = data + W * (N * (offset + 1 + i) + offset) + 1 + i + offset;
			char a = num[W];
			sprintf(num, "%*d", W, x + 4 * (n - 1) - 1 - i);
			num[W] = a;
		}
		fill_frame(W, N, n - 2, offset + 1, x + 4 * (n - 1), data);
	}
}

int main(int argc, char *argv[]) {
	char *file_name = argv[1];
	int fd = open(file_name, O_RDWR | O_CREAT, 0640);
	if (fd == -1) return 0;
	uint32_t N = strtol(argv[2], NULL, 10);
	uint32_t W = strtol(argv[3], NULL, 10);
	ftruncate(fd, (N * N * W + N) * sizeof(char));
	char *contents = mmap(NULL,
			(N * N * W + N) * sizeof(char),
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			fd,
			0);
	fill_frame(W, N, N, 0, 1, contents);
	for (int i = 0; i < N; i++) contents[W * (N * i + N) + i] = '\n';
	msync(contents, (N * N * W + N) * sizeof(char), MS_SYNC);
	munmap(contents, (N * N * W + N) * sizeof(char));
	close(fd);
	return 0;
}
