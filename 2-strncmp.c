#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
/**
 * _strncmp - compares string
 * @str1: first string to compare
 * @str2: second string to compare
 * @n: size of strings
 * Return: expected results
 */
int _strncmp(char *str1, char *str2, size_t n)
{
	if (str1 == NULL && str2 == NULL)
		return (0);
	else if (str1 == NULL)
		return (-1);
	else if (str2 == NULL)
		return (1);
	for (size_t i = 0; i < n; i++)
	{
		if (str1[i] != str2[i])
		{
			return ((unsigned char) str1[i] - (unsigned char) str2[i]);
		}
		if (str1[i] == '\0' || str2[i] == '\0')
		{
			break;
		}
	}
	return (0);
}
