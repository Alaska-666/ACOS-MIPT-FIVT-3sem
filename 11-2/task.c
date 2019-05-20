#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <limits.h>
#include <sys/stat.h>

void directory(const char* file, int64_t* count) {
	DIR* dir = opendir(file);
	struct dirent* element;
	if (!dir) return;
	element = readdir(dir);
	do  {
		char path[PATH_MAX];
		strcpy(path, file);
		strcat(path, "/");
		strcat(path, element->d_name);
		if (element->d_type == DT_REG) {
                        struct stat st;
                        if (lstat(path, &st) != -1) *count += st.st_size;
                }
 		else if(element->d_type == DT_DIR) {
			char tmp[NAME_MAX];
			strcpy(tmp, element->d_name);
			if (strcmp(tmp, ".") == 0 || strcmp(tmp, "..") == 0) continue;
			directory(path, count);
		}
	} while ((element = readdir(dir)) != NULL);
	closedir(dir);
}

int main(int argc, char* argv[]) {
	int64_t size = 0;
	directory(argv[1], &size);
	printf("%lld\n", size);
	return 0;
}
