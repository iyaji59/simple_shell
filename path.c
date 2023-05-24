#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#define MAX_COMMAND_LENGTH 100
/**
 * search_in_path - find a path
 * @command: command to find path of
 * Return: command when found
 */
char *search_in_path(char *command)
{
	char *path = _getenv("PATH");

	if (path == NULL)
	{
		perror("PATH environment variable not set\n");
		return (NULL);
	}
	char *token;

	token = my_strtok(path, ":");
	while (token != NULL)
	{
		int token_length = _strlen(token);
		int command_length = _strlen(command);

		if (token_length + command_length + 2 > MAX_COMMAND_LENGTH)
		{
			perror("Command path is too long\n");
			return (NULL);
		}
		static char full_path[MAX_COMMAND_LENGTH];

		_strcpy(full_path, token);
		full_path[token_length] = '/';
		_strcpy(full_path + token_length + 1, command);
		if (access(full_path, X_OK) == 0)
		{
			return (_strdup(full_path));
		}
		token = my_strtok(NULL, ":");
	}
	return (NULL);
}
/**
 * find_command - find path
 * @command: command to find
 * Return: full path
 */
char *find_command(char *command)
{
	if (_strchr(command, '/') == NULL)
	{
		char *path_command = search_in_path(command);

		if (path_command != NULL)
		{
			return (path_command);
		}
		static char full_path[MAX_COMMAND_LENGTH];

		_strcpy(full_path, "/bin/");
		_strncpy(full_path + 5, command, sizeof(full_path) - 6);
		full_path[MAX_COMMAND_LENGTH - 1] = '\0';
		return (_strdup(full_path));
	}
	else
	{
		struct stat st;

		if (access(command, X_OK) != 0 || stat(command, &st) != 0
				|| !(st.st_mode & S_IFREG))
		{
			return (NULL);
		}
		return (_strdup(command));
	}
}
