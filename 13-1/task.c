#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int N = strtol(argv[1], NULL, 10);
	pid_t pid;
	for (int i = 0; i < N; i++) {
		pid = fork();
		if (pid ==  0) {
			if (i < N - 1) printf("%d ", i + 1);
			else printf("%d\n", i + 1);
			exit(0);
		}
		int status;
		waitpid(pid, &status, 0);
	}
	return 0;
}
