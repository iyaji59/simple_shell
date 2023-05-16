#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
/**
 * readline - reads input from user
 */
#define READ_LINE_SIZE 1024
char *readline(void)
{
	char *command = malloc(READ_LINE_SIZE);
	size_t line_size = READ_LINE_SIZE;
	ssize_t read;

	while (1)
	{
		printf("$ ");
		fflush(stdout);
		read = getline(&command, &line_size, stdin);
		if (read == -1)
		{
			free(command);
			exit(EXIT_SUCCESS);
		}
		if (command[read - 1] == '\n')
		{
			command[read - 1] = '\0';
			command[read] = '\0';
		}
		execute_command(command);
	}
	free(command);
	return (EXIT_SUCCESS);

}

/**
 * execute_command - execute user input
 * @command: user input
 */
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Error: fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *argv[] = {command, NULL};

		execve(command, argv, environ);
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}
