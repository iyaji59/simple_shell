#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char *path = getenv("PATH"); // get the PATH environment variable
    char *dir;
    char *token;
    char *filename;
    char filepath[1024];

    if (argc < 2) {
        printf("Usage: %s filename ..\n", argv[0]);
        return 1;
    }

filename = argv[1];

    // tokenize the PATH variable
    token = strtok(path, ":");

    while (token != NULL) {
        // concatenate the directory and the filename
        dir = token;
        snprintf(filepath, sizeof(filepath), "%s/%s", dir, filename);

        // check if the file exists
        if (access(filepath, F_OK) != -1) {
            printf("%s\n", filepath);
            return 0;
        }

        // get the next directory in the PATH
        token = strtok(NULL, ":");
    }

    printf("%s: command not found\n", filename);
    return 1;
}
