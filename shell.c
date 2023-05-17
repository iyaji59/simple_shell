#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include "readline.c"
/**
 * main - main function
 * @ac: argument count
 * @argv: argument value
 * Return: return 0
 */
int main(void)
{
	while(1)
	{
		readline();
	}
	return (0);
}
