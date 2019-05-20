#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>


int main() {
	char prog[2048];
	char buff[2048];
	fgets(buff, sizeof(buff), stdin);
	if (strnlen(buff, sizeof(buff)) == 0) {
		return 0;
	}
	char* slash = strchr(buff, '\n');
	if (slash) {
		*slash = '\0';
	}
	int f = open("file.c", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	snprintf(prog, sizeof(prog), "#include <stdio.h>\n int main() { int value = (%s); printf(\"%%d\", value); return 0; }", buff);
	write(f, prog, strnlen(prog, sizeof(prog)));
	close(f);
	pid_t pid = fork();
	if (pid != 0) {
		int wstatus;
		waitpid(pid, &wstatus, 0);
	}
	else {
		execlp("gcc", "gcc", "-o", "file", "file.c", NULL);
                exit(0);
	}
	execlp("./file", "./file", NULL);
	return 0;
}
