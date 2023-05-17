#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
extern char**environ;
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

void prompt() {
    write(STDOUT_FILENO, "$ ", 2);
}

char *find_command(char *command) {
    static char full_path[MAX_COMMAND_LENGTH];

    // Check if the command contains a directory path
    if (strchr(command, '/') != NULL) {
        if (access(command, X_OK) == 0) {
            strncpy(full_path, command, sizeof(full_path));
            return full_path;
        }
        return NULL;
    }

    // Search for the command in /bin directory
    snprintf(full_path, sizeof(full_path), "/bin/%s", command);
    if (access(full_path, X_OK) == 0) {
        return full_path;
    }

    char *path = getenv("PATH");

    if (path == NULL) {
        fprintf(stderr, "PATH environment variable not set\n");
        return NULL;
    }

    char *token;
    char *saveptr;
    token = strtok_r(path, ":", &saveptr);

    while (token != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", token, command);

        if (access(full_path, X_OK) == 0) {
            return full_path;
        }

        token = strtok_r(NULL, ":", &saveptr);
    }

    return NULL;
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
    char *token = strtok(command, " ");

    while (token != NULL) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }

    args[i] = NULL;

    return i;
}

int main() {
    char *command = NULL;
    size_t command_length = 0;
    ssize_t bytes_read;

    while (1) {
        prompt();

        bytes_read = getline(&command, &command_length, stdin);

        if (bytes_read == -1) {
            // End of file (Ctrl+D)
            break;
        }

        // Remove the trailing newline character
        command[strcspn(command, "\n")] = '\0';

        char *args[MAX_ARGS];
        int arg_count = parse_arguments(command, args);

        if (arg_count > 0) {
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
