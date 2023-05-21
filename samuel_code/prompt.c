#include "shell.h"

/**
 * prompt_loop - a function that continouly loop the prompt
 * Return: 0
 */

void prompt_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("$ "); /* Prompt to display */
		line = readLine(); /* reading the line of input */
		args = _split_line(line); /* splitting the lines into argument */
		status = _execute(args); /* checking for the when to exit */

		free(line);
		free(args);
	} while (status);
}
