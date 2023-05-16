#include "shell.h"
#include "readline.c"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 * main - main shell entry
 * @argc: argument count
 * @argv: argument value
 * Return: return 0 for success
 */
int main(int argc, char **argv)
{
	readline();
	return (0);
}
