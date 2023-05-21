#include "shell.h"
/**
 * _launch - to lauch a program
 * @args: numbers of argument to be launch
 * Return: 1
 */

int _launch(char **args)
{
	pid_t pid; 
	int status;

	pid = fork();

	/* child process */
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("./shell");
		}
		exit(EXIT_FAILURE);
	}
	/* Error checking */
	else if (pid < 0)
	{
		perror("./shell");
	}

	else
	{
		wait(&status);
		WEXITSTATUS(status);
	}
	return (1);
}
