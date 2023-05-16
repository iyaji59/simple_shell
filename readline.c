#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#define DELIM_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"
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
		char *args[DELIM_BUFSIZE + 1];

		split_line(command, args);
		execute_command(args);

	}
	free(command);
	return (EXIT_SUCCESS);

}

/**
 * execute_command - execute user input
 * @command: user input
 */
void execute_command(char **command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Error: fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(command[0], command, environ);
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}
/**
 * split_line - tokenize command from user
 * @line: input to split
 * @args: array to store tokenize input
 * Return: tokenize string
 */
void split_line(char *line, char **args)
{
	char *token;
	int argc = 0;

	token = strtok(line, TOK_DELIM);
	while (token != NULL && argc < DELIM_BUFSIZE)
	{
		args[argc] = token;
		argc++;
		token = strtok(NULL, TOK_DELIM);
	}
	args[argc] = NULL;
}
