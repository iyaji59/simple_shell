#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define LINE_BUFSIZE 1024
/**
 * getline - read a line of input from the user
 * Return: buffer to the input
 */
char *line(void)
{
	int bufsize = LINE_BUFSIZE;
	char *buffer = malloc(sizeof(char) * bufsize);
	int line;
	int position = 0;

	if (buffer == NULL)
		printf("allocation failed\n");
	while (1)
	{
		/*read a character*/
		line = getchar();
		if (line == EOF || line == '\n')
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
		{
			buffer[position] = line;
		}
		position++;
		/* if we exceed the buffer reallocate */
		if (position >= bufsize)
		{
			bufsize += LINE_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (buffer == NULL)
				printf("allocation failed\n");
		}
	}

}
