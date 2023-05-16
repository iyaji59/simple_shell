#include "shell.h"
#include "getline.c"
#include <stdio.h>
#include <unistd.h>
/**
 * main - main function
 * Return: 0 for success
 */
int main(void)
{
	char *str = NULL;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		str = line();
		if (str == NULL)
			return (-1);
		printf("%s\n", str);
		free(str);
	}
	return (0);
}
