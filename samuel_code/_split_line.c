#include "shell.h"

/**
 * _split_line - all about parsing the line
 * Return: Tokens
 */

#define TOK_BUFFER_SIZE 64
#define TOK_DELIM " \t\r\n\a"

char **_split_line(char *line)
{
	int buffer_size = TOK_BUFFER_SIZE, current = 0;
	char **tokens = malloc(buffer_size * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "hsh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOK_DELIM);

	while (token != NULL)
	{
		tokens[current] = token;
		current++;

		if (current >= buffer_size)
		{
			buffer_size += TOK_BUFFER_SIZE;
			tokens = realloc(tokens, buffer_size * sizeof(char *));

			if (!tokens)
			{
				fprintf(stderr, "hsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[current] = NULL;
	return (tokens);
}
