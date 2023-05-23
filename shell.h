#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
void process_alias_command(char **args);
void add_alias(char *name, char *value);
void print_aliases();
void execute_commands(char *command, char **args);
void custom_cd(const char *directory);
extern char **environ;
int _unsetenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
char *my_strtok(char *str, const char *delim);
ssize_t my_getline(char **lineptr, size_t *n);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
extern char **environ;
char *find_command(char *command);
void execute_command(char *command, char **args);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_getenv(char *name);
char *_strcpy(char *dest, char *src);
void log_ops(char *line, ssize_t *line_new);
#endif
