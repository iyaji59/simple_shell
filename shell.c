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
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10
void prompt() {
    write(STDOUT_FILENO, "$ ", 2);
}
char *find_command(char *command) {
    static char full_path[MAX_COMMAND_LENGTH];

    if (strchr(command, '/') == NULL) {
        char *path = _getenv("PATH");

        if (path == NULL) {
            fprintf(stderr, "PATH environment variable not set\n");
            return NULL;
        }
        char *token;
        token = my_strtok(path, ":");

        while (token != NULL) {
            int path_length = snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
            if (path_length >= sizeof(full_path)) {
                fprintf(stderr, "Command path is too long\n");
                return NULL;
            }
            if (access(full_path, X_OK) == 0) {
                return full_path;
            }
            token = my_strtok(NULL, ":");
        }
        snprintf(full_path, sizeof(full_path), "/bin/%s", command);
    } else {
        if (access(command, X_OK) != 0) {
            return NULL;
        }
        strncpy(full_path, command, sizeof(full_path) - 1);
    }
    return full_path;
}
void execute_command(char *command, char **args) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        execve(command, args, environ);

        // execve only returns if an error occurs
        perror("Command execution failed");
        exit(1);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
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
                    // No exit status provided, exit with 0
                    exit_shell(0);
                }
            }
	     else if (strcmp(args[0], "setenv") == 0) {
                // Set environment variable
                if (arg_count != 3) {
                    fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
                } else {
                    custom_setenv(args[1], args[2]);
                }
	     }
	     else if (strcmp(args[0], "unsetenv") == 0) {
                // Unset environment variable
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
