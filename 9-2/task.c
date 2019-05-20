#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

const uint32_t max_size = 1 * 1024 * 1024;

int32_t cmp(const void *a, const void *b) {
	int32_t *x = (int32_t*)a;
	int32_t *y = (int32_t*)b;
	return *x > *y;
}

void sort(char* filename, uint32_t* id) {
	int32_t input = open(filename, O_RDWR);
	uint32_t size = lseek(input, 0, SEEK_END);
	lseek(input, 0, SEEK_SET);
	if (size < max_size) {
		int32_t* buffer = (int32_t*)malloc(size);
		read(input, buffer, size);
		lseek(input, 0, SEEK_SET);
		qsort(buffer, size / sizeof(int32_t), sizeof(int32_t), cmp);
		write(input, buffer, size);
		return;
	}
	char name1[5], name2[5];
	sprintf(name1, "%d", *id);
	sprintf(name2, "%d", *id + 1);
	(*id) += 2;
	int32_t tmp1 = open(name1, O_WRONLY | O_CREAT, 0640);
	int32_t tmp2 = open(name2, O_WRONLY | O_CREAT, 0640);
	int32_t x = 0;
	bool tmp = false;
	while (read(input, &x, sizeof(int32_t)) > 0) {
		if (tmp) {
			write(tmp1, &x, sizeof(int32_t));
			tmp = false;
		}
		else {
			write(tmp2, &x, sizeof(int32_t));
			tmp = true;
		}
	}
	close(tmp1);
	close(tmp2);
	sort(name1, id);
	sort(name2, id);
	lseek(input, 0, SEEK_SET);
	tmp1 = open(name1, O_RDONLY);
	tmp2 = open(name2, O_RDONLY);
	int32_t tmp3, tmp4;
	while (read(tmp1, &tmp3, sizeof(int32_t)) > 0 && read(tmp2, &tmp4, sizeof(int32_t)) > 0) {
		if (tmp3 > tmp4) {
			write(input, &tmp4, sizeof(int32_t));
			lseek(tmp1, -sizeof(int32_t), SEEK_CUR);
		}
		else {
			write(input, &tmp3, sizeof(int32_t));
			lseek(tmp2, -sizeof(int32_t), SEEK_CUR);
		}
	}
	while (read(tmp1, &tmp3, sizeof(int32_t)) > 0) write(input, &tmp3, sizeof(int32_t));
	while (read(tmp2, &tmp4, sizeof(int32_t)) > 0) write(input, &tmp4, sizeof(int32_t));
	close(tmp1);
	close(tmp2);
	close(input);
}

int main(int32_t args, char* argv[]) {
	uint32_t id = 0;
	sort(argv[1], &id);
	return 0;
}
