#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 * _getenv - implementation to getenv
 * @name: name to get environmental value of
 * Return: return env or NULL
 */
char *_getenv(char *name)
{
	char **env = environ;
	size_t len = _strlen(name);

	while (*env != NULL)
	{
		if (_strncmp(name, *env, len) == 0)
		{
			if ((*env)[len] == '=')
			{
				return (*env + len + 1);
			}
		}
		env++;
	}
	return (NULL);
}
