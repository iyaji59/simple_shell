#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define PATH_MAX 1024
void custom_cd(const char *directory) {
    char *home = getenv("HOME");
    char *previous = getenv("PWD");
    char cwd[PATH_MAX];

    if (directory == NULL || strcmp(directory, "~") == 0) {
        if (home == NULL) {
            fprintf(stderr, "cd: HOME environment variable not set\n");
            return;
        }
        directory = home;
    } else if (strcmp(directory, "-") == 0) {
        if (previous == NULL) {
            fprintf(stderr, "cd: OLDPWD environment variable not set\n");
            return;
        }
        directory = previous;
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stderr, "cd: Failed to get current directory\n");
        return;
    }

    if (chdir(directory) != 0) {
        fprintf(stderr, "cd: Failed to change directory\n");
        return;
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stderr, "cd: Failed to update PWD\n");
        return;
    }

    if (previous != NULL) {
        setenv("OLDPWD", previous, 1);
    }
    setenv("PWD", cwd, 1);
}
