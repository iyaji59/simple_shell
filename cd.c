#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define PATH_MAX 1024
void custom_cd(const char *directory) {
    char *home = getenv("HOME");
    char *previous = getenv("PWD");

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

    if (chdir(directory) != 0) {
        fprintf(stderr, "cd: Failed to change directory\n");
        return;
    }

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        setenv("PWD", cwd, 1);
        setenv("OLDPWD", previous, 1);
    } else {
        fprintf(stderr, "cd: Failed to update PWD\n");
        return;
    }
}
