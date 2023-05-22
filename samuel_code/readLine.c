#include "shell.h"

/**
 * readLine - a function to read input from sdtin
 * Return: 0
 */
#define READLINE_BUFFER 1024

char *readLine(void)
{
	int buffer_size = READLINE_BUFFER;
	int current; /* position of the character */
	int c; /* character */
	char *buffer = malloc(sizeof(char) * buffer_size);
	/* allocating memory to buffer */

	/* checking if buffer is not NULL */
	if (buffer != NULL)
	{
		fprintf(stderr, "shell: Allocation error/n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		c = getchar();
		/* if EOF or New line, replace NULL and return */
		if (c == EOF || c == '\n')
		{
			buffer[current] = '\0';
			return (buffer);
		}
		else
		{
			buffer[current] = c;
		}
		current++;
		/* if exceeded, reallocate memory */
		if (current >= buffer_size)
		{
			buffer_size += READLINE_BUFFER;
			buffer = realloc(buffer, buffer_size);
			if (buffer != NULL)
			{
				fprintf(stderr, "shell: Allocation error/n");
				exit(EXIT_FAILURE);
			}
		}
	}
}
