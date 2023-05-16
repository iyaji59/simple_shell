#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
extern char **environ;
void execute_command(char *command);
char *readline(void);
size_t _strlen(char *ch);
#endif
