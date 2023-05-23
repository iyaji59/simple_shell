#include <stdio.h>
#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_ALIAS_LENGTH 100

typedef struct Alias {
    char *name;
    char *value;
    struct Alias *next;
} Alias;

Alias *alias_list = NULL;

void print_aliases() {
    Alias *current = alias_list;

    while (current != NULL) {
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
    }
}

Alias *find_alias(char *name) {
    Alias *current = alias_list;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void add_alias(char *name, char *value) {
    Alias *alias = find_alias(name);

    if (alias != NULL) {
        free(alias->value);
        alias->value = strdup(value);
    } else {
        Alias *new_alias = malloc(sizeof(Alias));
        new_alias->name = strdup(name);
        new_alias->value = strdup(value);
        new_alias->next = alias_list;
        alias_list = new_alias;
    }
}
void process_alias_command(char **args) {
    // If no arguments provided, print all aliases
    if (args[1] == NULL) {
        print_aliases();
        return;
    }

    // Iterate through the arguments and process each alias
    for (int i = 1; args[i] != NULL; i++) {
        char *equal_sign = strchr(args[i], '=');

        if (equal_sign != NULL) {
            // Argument in the form 'name=value'
            *equal_sign = '\0';
            char *name = args[i];
            char *value = equal_sign + 1;
            add_alias(name, value);
        } else {
            // Argument is only the name, print the alias if it exists
            Alias *alias = find_alias(args[i]);

            if (alias != NULL) {
                printf("%s=%s\n", alias->name, alias->value);
            }
        }
    }
}
