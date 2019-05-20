#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t pid;
	char word[4097];
	int counter = 0;
	int status;
	do {
		pid = fork();
		if (pid == 0) {
			if (scanf("%s", word) != EOF) return 1;
			return 0;

		}
		else {
                        waitpid(pid, &status, 0);
			counter = counter + WEXITSTATUS(status);

		}
	} while (status);
	printf("%d", counter);
	return 0;
}
