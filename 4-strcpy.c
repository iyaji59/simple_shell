#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * _strcpy - copi string from one destination to another
 * @dest: destination
 * @src: source
 * Return: copied string
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}
