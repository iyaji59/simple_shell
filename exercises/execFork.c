#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(void)
{
	int i, status;
	char *args[] = {"ls", "-l", "/tmp", NULL};
	// Null means end of the string/array here
	pid_t pid;
	// we want to loop 5 times
	for (i = 0; i < 5; i++)
	{
		pid = fork();
		if (pid == -1)
		{
			printf("fork error\n");
		}
		else if (pid == 0)
		{
			execve("/bin/ls", args, NULL);
			if (execve < 0)
				printf("error\n");
			exit(0);
		}
		else
		{
			wait(&status);
		}

	}
	return (0);
}
