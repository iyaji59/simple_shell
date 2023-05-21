#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
char *my_strtok(char *str, const char *delim) {
    static char *token = NULL;
    static char *nextToken = NULL;

    if (str != NULL) {
        token = str;
        nextToken = NULL;
    } else {
        if (nextToken == NULL) {
            return NULL;
        }
        token = nextToken;
    }

    if (*token == '\0') {
        return NULL;
    }

    char *delimPos = strpbrk(token, delim);
    if (delimPos != NULL) {
        *delimPos = '\0';
        nextToken = delimPos + 1;
    } else {
        nextToken = NULL;
    }

    return token;
}
