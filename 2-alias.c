#include "shell.h"

int status;

/**
 * free_aliases - free alias
 * @alias_ptr: pointer to head of linked list
 * Return: Success
 */
int free_aliases(alias *alias_ptr)
{
	alias *tmp;

	while (alias_ptr != NULL)
	{
		tmp = alias_ptr;
		alias_ptr = alias_ptr->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}

	return (TRUE);
}

/**
 * check_if_alias - if it's a command
 * @args: args
 * @alias_ptr: pointer to available alias
 * Return: TRUE
 */
int check_if_alias(char **args, alias *alias_ptr)
{
	while (alias_ptr != NULL)
	{
		if (str_compare(*args, alias_ptr->name, MATCH) == TRUE)
		{
			*args = _strdup(alias_ptr->value);
			return (DO_EXECVE);
		}
		alias_ptr = alias_ptr->next;
	}
	return (TRUE);
}

/**
 * print_aliases - prints to stdin
 * @alias_ptr: pointer to alias
 *
 * Return: SKIP_FORK
 */
int print_aliases(alias *alias_ptr)
{
	while (alias_ptr != NULL)
	{
		write(STDOUT_FILENO, alias_ptr->name, _strlen(alias_ptr->name));
		write(STDOUT_FILENO, "=", 2);
		write(STDOUT_FILENO, alias_ptr->value,
		      _strlen(alias_ptr->value));
		write(STDOUT_FILENO, "\n", 2);
		alias_ptr = alias_ptr->next;
	}
	return (SKIP_FORK);
}

/**
 * print_alias_value - prints to stdin
 * @arg: name of alias
 * @alias_ptr: pointer to alias
 * Return: TRUE or FALSE
 */
int print_alias_value(char *arg, alias *alias_ptr)
{
	while (alias_ptr != NULL)
	{
		fflush(stdin);
		if (str_compare(arg, alias_ptr->name, MATCH) == TRUE)
		{
			write(STDOUT_FILENO, arg, _strlen(arg));
			write(STDOUT_FILENO, "=", 2);
			write(STDOUT_FILENO, alias_ptr->value,
			      _strlen(alias_ptr->value));
			write(STDOUT_FILENO, "\n", 2);
			return (TRUE);
		}
		alias_ptr = alias_ptr->next;
	}

	status = 1;
	write(STDERR_FILENO, "alias: ", 7);
	write(STDERR_FILENO, arg, _strlen(arg));
	write(STDERR_FILENO, " not found\n", 11);

	return (FALSE);
}

/**
 * set_alias_value - set alias or update existing value
 * @arg: name of alias
 * @alias_ptr: pointer
 * @new_value: value of alias to be set
 * Return: TRUE
 */
int set_alias_value(char *arg, alias *alias_ptr, char *new_value)
{
	while (alias_ptr->next != NULL
	       && str_compare(alias_ptr->name, arg, MATCH) != TRUE)
	{
		alias_ptr = alias_ptr->next;
	}

	if (str_compare(alias_ptr->name, arg, MATCH) == TRUE)
	{
		free(alias_ptr->value);
	}
	else
	{
		alias_ptr->next = malloc(sizeof(alias *));
		alias_ptr = alias_ptr->next;
		if (alias_ptr == NULL)
			exit(EXIT_FAILURE);

		alias_ptr->name = _strdup(arg);
		alias_ptr->next = NULL;
	}
	alias_ptr->value = _strdup(new_value);

	return (TRUE);
}
