#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
size_t environ_size();
int _setenv(const char *name, const char *value, int overwrite);
int _setenv(const char *name, const char *value, int overwrite) {
    if (!name || name[0] == '\0' || strchr(name, '=') != NULL) {
        return -1;  // Invalid variable name
    }
    if (!overwrite && getenv(name) != NULL) {
        return 0;  // No modification needed
    }
    size_t len_name = strlen(name);
    size_t len_value = strlen(value);

    size_t len_total = len_name + len_value + 2;  // +2 for '=' and '\0'
    char *var = (char *)malloc(len_total);
    if (var == NULL) {
        return -1;  // Error allocating memory
    }
    snprintf(var, len_total, "%s=%s", name, value);
    for (int i = 0; environ[i] != NULL; ++i) {
        if (strncmp(environ[i], name, len_name) == 0 && environ[i][len_name] == '=') {
            free(environ[i]);
            environ[i] = var;
            return 0;  // Success
        }
    }
    char **new_environ = (char **)malloc((environ_size() + 2) * sizeof(char *));
    if (new_environ == NULL) {
        free(var);
        return -1;  // Error allocating memory
    }
    int j;

    for (j = 0; environ[j] != NULL; ++j) {
        new_environ[j] = environ[j];
    }
    new_environ[j] = var;
    new_environ[j + 1] = NULL;
    environ = new_environ;
    return 0;  // Success
}
size_t environ_size() {
    size_t count = 0;
    while (environ[count] != NULL) {
        count++;
    }
    return count;
}
int _unsetenv(const char *name) {
    if (!name || name[0] == '\0' || strchr(name, '=') != NULL) {
        return -1;  // Invalid variable name
    }

    size_t len_name = strlen(name);

    // Iterate through the environment variables
    for (int i = 0; environ[i] != NULL; ++i) {
        if (strncmp(environ[i], name, len_name) == 0 && environ[i][len_name] == '=') {
            // Shift the remaining elements and set the last element to NULL
            for (int j = i; environ[j] != NULL; ++j) {
                environ[j] = environ[j + 1];
            }
            return 0;  // Success
        }
    }

    return 0;  // Variable not found
}

int custom_setenv(const char *name, const char *value) {
    if (name == NULL || value == NULL) {
        fprintf(stderr, "setenv: Invalid arguments\n");
        return -1;
    }

    if (_setenv(name, value, 1) != 0) {
        fprintf(stderr, "setenv: Failed to set environment variable\n");
        return -1;
    }

    return 0;
}

int custom_unsetenv(const char *name) {
    if (name == NULL) {
        fprintf(stderr, "unsetenv: Invalid argument\n");
        return -1;
    }

    if (_unsetenv(name) != 0) {
        fprintf(stderr, "unsetenv: Failed to unset environment variable\n");
        return -1;
    }

    return 0;
}
