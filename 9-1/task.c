#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

int main(int args, char* argv[]) {
	int file = open(argv[1], O_RDONLY);
	//проверка на несуществующий файл
	if (file < 0) {
		return 1;
	}
	int value = 0;
	uint32_t next_pointer = 0;
	//проверка на пустой существующий
	if (read(file, &value, sizeof(value)) <= 0) {
		close(file);
		return 0;
	}
	read(file, &next_pointer, sizeof(next_pointer));
	printf("%d\n", value);
	while (next_pointer > 0) {
		lseek(file, next_pointer, SEEK_SET);
		read(file, &value, sizeof(value));
		read(file, &next_pointer, sizeof(next_pointer));
		printf("%d\n", value);
	}
	close(file);
	return 0;
}
