#include "shell.h"
/**
 * log_ops - logical operators "||" or "&&".
 * @line: PTR to the character to check in the line.
 * @new_len: PTR to new_len in get_new_len function.
 */
void log_ops(char *line, ssize_t *new_len)
{
	char prev, curr, nxt;

	prev = *(line - 1);
	curr = *line;
	nxt = *(line + 1);

	if (curr == '&')
	{
		if (nxt == '&' && prev != ' ')
			(*new_len)++;
		else if (prev == '&' && nxt != ' ')
			(*new_len)++;
	}
	else if (curr == '|')
	{
		if (nxt == '|' && prev != ' ')
			(*new_len)++;
		else if (prev == '|' && nxt != ' ')
			(*new_len)++;
	}
}
