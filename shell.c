#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "2-setenv.c"
#include "shell.h"
#include "2-strtok.c"
#include "2-getline.c"
#include "2-getenv.c"
#include "cd.c"
#include "alias.c"
#include "2-strchr.c"
#include "2-strlen.c"
#include "2-strncpy.c"
#include "3-strcmp.c"
#include "3-strspn.c"
#include "4-strcpy.c"
#include "4-strpbrk.c"
#include "5-strdup.c"
#include "path.c"
#include "2-strncmp.c"
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10
char exit_status_variable[16];
void replace_variable(char *arg, const char *variable, const char *replacement) {
    char *variable_ptr = strstr(arg, variable);
    if (variable_ptr != NULL) {
        char new_arg[MAX_COMMAND_LENGTH];
        strncpy(new_arg, arg, variable_ptr - arg);
        new_arg[variable_ptr - arg] = '\0';
        strncat(new_arg, replacement, sizeof(new_arg) - strlen(new_arg) - 1);
        strcat(new_arg, variable_ptr + strlen(variable));
        strcpy(arg, new_arg);
    }
}
int parse_arguments(char *command, char **args);
void prompt() {
    write(STDOUT_FILENO, "$ ", 2);
}
char *getpid_str() {
    static char pid_str[16];
    sprintf(pid_str, "%d", getpid());
    return pid_str;
}
void execute_command(char *command, char **args) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
	int i;
        for (i = 0; args[i] != NULL; i++) {
            replace_variable(args[i], "$?", exit_status_variable);
            replace_variable(args[i], "$$", getpid_str());
        }
        execve(command, args, environ);
        perror("Command execution failed");
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        sprintf(exit_status_variable, "%d", WEXITSTATUS(status));
    }
}
int parse_arguments(char *command, char **args) {
    int i = 0;
    char *token = my_strtok(command, " ");

    while (token != NULL) {
        args[i] = token;
        i++;
        token = my_strtok(NULL, " ");
    }

    args[i] = NULL;

    return i;
}
/**
 *
 */
void exit_shell(int status) {
    exit(status);
}
/**
 *
 */
int main() {
    char *command = NULL;
    size_t bufsize = 0;
    ssize_t bytes_read;

    while (1){
        prompt();
	bytes_read = my_getline(&command, &bufsize);
        if (bytes_read == -1) {
            break;
        }
        command[strcspn(command, "\n")] = '\0';
        char *args[MAX_ARGS];
        int arg_count = parse_arguments(command, args);

        if (arg_count > 0) {
	     if (strcmp(args[0], "exit") == 0) {
		 if (arg_count > 1) {
                 int exit_status = atoi(args[1]);
                 exit_shell(exit_status);
                } else {
                   
                    exit_shell(0);
                }
            }
	     else if (strcmp(args[0], "setenv") == 0) {
              
                if (arg_count != 3) {
                    fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
                } else {
                    custom_setenv(args[1], args[2]);
                }
	     }
	     else if (strcmp(args[0], "unsetenv") == 0) {
                if (arg_count != 2) {
                    fprintf(stderr, "Usage: unsetenv VARIABLE\n");
                } else {
                    custom_unsetenv(args[1]);
                }
	     }
	     if (strcmp(args[0], "cd") == 0) {
    		if (arg_count > 1) {
        		custom_cd(args[1]);
    		} else {
        		custom_cd(NULL);
    		}
    		continue;
            
	     }
	     if (strcmp(args[0], "alias") == 0) {
                    process_alias_command(args);
                         continue;
             }
            char *command_path = find_command(args[0]);

            if (command_path != NULL) {
                execute_command(command_path, args);
            } else {
                fprintf(stderr, "Command not found: %s\n", args[0]);
            }
        }
    }
    free(command);
    return 0;
}
