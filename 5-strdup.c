#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 * Return: return duplicated string
 */
char *_strdup(char *str)
{
	char *dup = malloc(_strlen(str) + 1);

	if (dup == NULL)
	{
		return (NULL);
	}
	_strcpy(dup, str);
	return (dup);
}
