#include "shell.h"

/**
 * log_ops - a function that checks for logical operators
 * @line: pointer to the char to check in the line
 * @line_new: A pointer to line_new
 */

void log_ops(char *line, ssize_t *line_new)
{
	char prev, curr, nxt;

	prev = *(line - 1);
	current = *line;
	nxt = *(line + 1);

	/* Handling the OR '|' logical operator */
	if (curr == '|')
	{
		if (nxt == '|' && prev != ' ')
			(*line_new)++;
		else if (prev == '|' && nxt != ' ')
			(*line_new)++;
	}

	/* Handling the AND '&' logical operator */
	else if (curr == '&')
	{
		if (nxt == '&' && prev != ' ')
			(*line_new)++;
		else if (prev == '&' && nxt != ' ')
			(*line_new)++;
	}
}
