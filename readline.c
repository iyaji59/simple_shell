#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#define DELIM_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10
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

		int arg_count = split_line(command, args);
		if (arg_count > 0)
		{
			char *path = find_command(args[0]);

			if (path != NULL)
			{
				execute_command(path, args);
			}
			else
			{
				perror("Command not found:%s\n");
			}
		}

	}
	free(command);
	return (EXIT_SUCCESS);

}

/**
 * execute_command - execute user input
 * @command: user input
 */
void execute_command(char *command, char **args)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Error: fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(command, args, environ);
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
	}
}
/**
 * split_line - tokenize command from user
 * @line: input to split
 * @args: array to store tokenize input
 * Return: tokenize string
 */
int split_line(char *line, char **args)
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
/**
 *
 */
char *find_command(char *command) {
    static char full_path[MAX_COMMAND_LENGTH];
    if (strchr(command, '/') != NULL) {
        if (access(command, X_OK) == 0) {
            strncpy(full_path, command, sizeof(full_path));
            return full_path;
        }
        return NULL;
    }
    snprintf(full_path, sizeof(full_path), "/bin/%s", command);
    if (access(full_path, X_OK) == 0) {
        return full_path;
    }
    char *path = getenv("PATH");

    if (path == NULL) {
        fprintf(stderr, "PATH environment variable not set\n");
        return NULL;
    }
    char *token;
    char *saveptr;

    token = strtok_r(path, ":", &saveptr);
    while (token != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
        if (access(full_path, X_OK) == 0) {
            return full_path;
        }
        token = strtok_r(NULL, ":", &saveptr);
    }
    return NULL;
}
