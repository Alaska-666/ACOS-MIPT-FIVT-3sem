#include <windows.h>
#include <stdio.h>

int main(int args, char* argv[]) {
	DWORD dwShareMode = 0;
	HANDLE file = CreateFileA(argv[1], GENERIC_READ, dwShareMode, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
	if (dwShareMode != 0) {
		DeleteFileA(argv[1]);
		return 1;
	}
	DWORD value = -1;
	DWORD next_pointer = -1;
	DWORD readed = 0;
	ReadFile(file, &value, sizeof(value), &readed, NULL);
	if (readed == 0) {
		DeleteFileA(argv[1]);
		return 0;
	}
	ReadFile(file, &next_pointer, sizeof(next_pointer), NULL, NULL);
	printf("%d\n", value);
	while (next_pointer > 0) {
		SetFilePointer(file, next_pointer, NULL, FILE_BEGIN);
		ReadFile(file, &value, sizeof(value), NULL, NULL);
		ReadFile(file, &next_pointer, sizeof(next_pointer), NULL, NULL);	
		printf("%d\n", value);
	}
	DeleteFileA(argv[1]);
	return 0;
}
