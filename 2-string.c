#include "shell.h"

/**
 *  _strlen - finds length of a string
 * @str: string whose length is being sought after
 * Return: the length
 */
int _strlen(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);

	while (*str != '\0')
	{
		i++;
		str++;
	}

	return (i);
}

/**
 * _strdup - allocates a space in memory for a copy of a string
 * @src: string a copy is made of
 * Return: pointer to memory or NULL
 */
char *_strdup(char *src)
{
	int len = _strlen(src);
	char *dest = malloc(len + 1);
	char *ptr;

	if (src == NULL)
		return NULL;
	if (dest == NULL)
		exit(EXIT_FAILURE);

	ptr = dest;

	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	*ptr = '\0';

	return (dest);
}

/**
 * str_concat - concate 2 strings
 * @s1: first string
 * @s2: second string
 * Return: a pointer or FAILURE
 */
char *str_concat(char *s1, char *s2)
{
	int len1 = (s1 != NULL) ? _strlen(s1) : 0;
	int len2 = (s2 != NULL) ? _strlen(s2) : 0;
	int len = len1 + len2;
	char *dest = malloc(len + 1);
	char *ptr = dest;

	if (dest == NULL)
	{
		exit(EXIT_FAILURE);
	}
	if (s1 != NULL)
	{
		while (*s1 != '\0')
		{
			*ptr = *s1;
			ptr++;
			s1++;
		}
	}
	if (s2 != NULL)
	{
		while (*s2 != '\0')
		{
			*ptr = *s2;
			ptr++;
			s2++;
		}
	}
	*ptr = '\0';
	return dest;
}
/**
 * str_compare - compare two string
 * @s1: first string
 * @s2: second string
 * @pref_or_match: prefix
 * Return: difference between strings
 */
int str_compare(char *s1, char *s2, int pref_or_match)
{
	if (s1 == NULL || s2 == NULL)
		return (FALSE);

	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (FALSE);

		s1++;
		s2++;
	}

	if (pref_or_match == PREFIX)
		return (TRUE);

	if (*s1 == *s2)
		return (TRUE);

	return (FALSE);
}
