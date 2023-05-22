#include "shell.h"
/**
 * _get_new_len - length of ";", "||", "&&&", or "#".
 * @line: line to check.
 * Return: The new length of the line.
 */

ssize_t _get_new_len(char *line)
{
	size_t i;
	ssize_t new_len = 0;
	char curr, nxt;

	for (i = 0; line[i]; i++)
	{
		curr = line[i];
		nxt = line[i + 1];
		if (curr == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (curr == ';')
			{
				if (nxt == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[i - 1] == ';' && nxt != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					new_len++;
				if (nxt != ' ')
					new_len++;
			}
			else
				log_ops(&line[i], &new_len);
		}
		else if (curr == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_len++;
			if (nxt != ' ' && nxt != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}
