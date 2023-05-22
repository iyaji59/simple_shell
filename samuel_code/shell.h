#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void prompt_loop(void);
char *readLine(void);
int _launch(char **args);
int _execute(char **args);
char **_split_line(char *line);
void sig_handler(int sig);
int execute(char **args, char **front);
#endif
