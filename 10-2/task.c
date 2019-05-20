#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

int main() {
	struct stat st;
	char file_name[PATH_MAX];
	char* nl;
	while (fgets(file_name, sizeof(file_name), stdin)) {
		nl = memchr(file_name, '\n', sizeof(file_name));
		if (nl) *nl = '\0';
		if (lstat(file_name, &st) == 0 && S_ISLNK(st.st_mode)) {
			char tmp[PATH_MAX];
			ssize_t size = readlink(file_name, tmp, sizeof(tmp));
			tmp[size] = '\0';
			char* file = dirname(file_name);
			strcat(file, "/");
			strcat(file, tmp);
			realpath(file, tmp);
			puts(tmp);
		}
		else if (lstat(file_name, &st) == 0 && S_ISREG(st.st_mode)) {
			char link_name[PATH_MAX];
			strcpy(link_name, "link_to_");
			nl = basename(file_name);
			strcat(link_name, nl);
			symlink(file_name, link_name);
		}
	}
	return 0;
}
