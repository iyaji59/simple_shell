#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
#include "2-strtok.c"
#include "2-getline.c"
extern char**environ;
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10
void prompt() {
    write(STDOUT_FILENO, "$ ", 2);
}
char *find_command(char *command) {
    static char full_path[MAX_COMMAND_LENGTH];

    if (strchr(command, '/') == NULL) {
        char *path = getenv("PATH");

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

int main() {
    char *command = NULL;
    size_t bufsize = 0;
    ssize_t bytes_read;

    // Reading lines until end of file or error
    while (1){
        prompt();
	bytes_read = my_getline(&command, &bufsize);
        if (bytes_read == -1) {
            // End of file (Ctrl+D)
            break;
        }

        // Remove the trailing newline character
        command[strcspn(command, "\n")] = '\0';

        char *args[MAX_ARGS];
        int arg_count = parse_arguments(command, args);

        if (arg_count > 0) {
	     if (strcmp(args[0], "exit") == 0) {
                // Exit the shell
                      break;
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
