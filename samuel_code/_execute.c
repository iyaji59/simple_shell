#include "shell.h"

/**
 * execute - execute a command in a child process
 * Return: launch the process
 */

int _execute(char **args)
{
	/* check if an empty command was entered */
	if (args[0] == NULL)
	{
		return (1);
	}
	return _launch(args);
}
