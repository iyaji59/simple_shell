#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
/**
 * my_strtok - split command and arguments
 * @str: string to split
 * @delim: delimiters
 * Return: an array
 */
char *my_strtok(char *str, char *delim)
{
	static char *token;
	static char *nextToken;

	if (str != NULL)
	{
		token = str;
		nextToken = NULL;
	}
	else
	{
		if (nextToken == NULL)
			return (NULL);
		token = nextToken;
	}
	if (*token == '\0')
		return (NULL);
	char *delimPos = _strpbrk(token, delim);

	if (delimPos != NULL)
	{
		*delimPos = '\0';
		nextToken = delimPos + 1;
	}
	else
	{
		nextToken = NULL;
	}
	return (token);
}
