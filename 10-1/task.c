#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main() {
	char file[PATH_MAX];
	struct stat st;
	char *nl;
	while (fgets(file, sizeof(file), stdin)) {
		nl = memchr(file, '\n', sizeof(file));
		if (nl) *nl = '\0';
		int fd = open(file, O_RDONLY);
		if (fd > 0 && fstat(fd, &st) != -1 && st.st_mode & S_IXUSR) {
			if (lseek(fd, 0, SEEK_END) < 2) {puts(file); continue; }
			lseek(fd, 0, SEEK_SET);
			char hash, mark;
			read(fd, &hash, sizeof(char));
			read(fd, &mark, sizeof(char));
			if (hash == '#' && mark == '!') {
                        	char buffer[PATH_MAX];
                                read(fd, buffer, PATH_MAX * sizeof(char));
                                nl = memchr(buffer, '\n', sizeof(buffer));
                                if (nl) *nl = '\0';
                                struct stat intp;
                       		if (stat(buffer, &intp) == -1 || !(intp.st_mode & S_IXUSR)) puts(file);
                        } else {
				lseek(fd, 0, SEEK_SET);
                        	char d = -1,e = -1,l = -1,f = -1;
                        	read(fd, &d, sizeof(char));
				read(fd, &e, sizeof(char));
                        	read(fd, &l, sizeof(char));
                        	read(fd, &f, sizeof(char));
				if (d != 0x7f || e != 'E' || l != 'L' || f != 'F') puts(file);
			}
		}
	}
	return 0;
}
