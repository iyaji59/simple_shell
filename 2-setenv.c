#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
/**
 * _setenv - set environmental variable
 * @name: variable name
 * @value: variable value
 * @overwrite: overwrite parameter
 * Return: return 0 for success
 */
int _setenv(char *name, char *value, int overwrite)
{
	if (!name || name[0] == '\0' || _strchr(name, '=') != NULL)
		return (-1);
	if (!overwrite && _getenv(name) != NULL)
		return (0);
	size_t len_name = _strlen(name);
	size_t len_value = _strlen(value);
	size_t len_total = len_name + len_value + 2;
	char *var = (char *)malloc(len_total);

	if (var == NULL)
		return (-1);
	_strcpy(var, name);
	var[len_name] = '=';
	_strcpy(var + len_name + 1, value);
	for (int i = 0; environ[i] != NULL; ++i)
	{
		if (_strncmp(environ[i], name, len_name) == 0 && environ[i][len_name] == '=')
		{
			free(environ[i]);
			environ[i] = var;
			return (0);
		}
	}
	char **new_environ = (char **)malloc((environ_size() + 2) * sizeof(char *));

	if (new_environ == NULL)
	{
		free(var);
		return (-1);
	}
	int j;

	for (j = 0; environ[j] != NULL; ++j)
		new_environ[j] = environ[j];
	new_environ[j] = var;
	new_environ[j + 1] = NULL;
	environ = new_environ;
	return (0);
}
/**
 * environ_size - environ size
 * Return: count of environ
 */
size_t environ_size(void)
{
	size_t count = 0;

	while (environ[count] != NULL)
		count++;
	return (count);
}
/**
 * _unsetenv - unset variable value
 * @name: name of environmental variable
 * Return: 0 for success
 */
int _unsetenv(char *name)
{
	if (!name || name[0] == '\0' || _strchr(name, '=') != NULL)
		return (-1);
	size_t len_name = _strlen(name);

	for (int i = 0; environ[i] != NULL; ++i)
	{
		if (strncmp(environ[i], name, len_name) == 0 && environ[i][len_name] == '=')
		{
			for (int j = i; environ[j] != NULL; ++j)
				environ[j] = environ[j + 1];
			return (0);
		}
	}
	return (0);
}
/**
 * custom_setenv - set environmental variable and value
 * @name: name of variable
 * @value: value of variable
 * Return: 0 for success
 */
int custom_setenv(char *name, char *value)
{
	if (name == NULL || value == NULL)
	{
		perror("setenv: Invalid arguments\n");
		return (-1);
	}
	if (_setenv(name, value, 1) != 0)
	{
		perror("setenv: Failed to set environment variable\n");
		return (-1);
	}
	return (0);
}
/**
 * custom_unsetenv - unset a variable
 * @name: name of variable
 * Return: 0 for success
 */
int custom_unsetenv(char *name)
{
	if (name == NULL)
	{
		perror("unsetenv: Invalid argument\n");
		return (-1);
	}
	if (_unsetenv(name) != 0)
	{
		perror("unsetenv: Failed to unset environment variable\n");
		return (-1);
	}
	return (0);
}
