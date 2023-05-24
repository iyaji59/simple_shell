#include "shell.h"

/**
 * read_input - reads input from the terminal
 * @is_separated: flag indicating if the input is separated
 *
 * Return: input string or NULL on failure
 */
char *read_input(int *is_separated)
{
    char *input = NULL;
    size_t buf_size = 0;
    ssize_t bytes_read;

    if (*is_separated == FALSE)
    {
        if (isatty(STDIN_FILENO) == 1)
            write(STDOUT_FILENO, "my_shell$ ", 10);
        bytes_read = getline(&input, &buf_size, stdin);
        if (bytes_read == -1)
            return NULL;
        if (bytes_read == 1)
            return input;
        input[bytes_read - 1] = '\0';
        input = input_san(input, &buf_size);
        if (buf_size == 0)
            return input;
    }
    else
    {
        input = NULL;
        bytes_read = getline(&input, &buf_size, stdin);
        if (bytes_read == -1)
            return NULL;
        if (bytes_read == 1)
            return input;
        input[bytes_read - 1] = '\0';
        input = input_san(input, &buf_size);
        if (buf_size == 0)
            return input;
        *is_separated = FALSE;
    }
    return input;
}

/**
 * execute_command - executes a single command
 * @input: input command to execute
 * @is_separated: flag indicating if the input is separated
 * @line_num: current line number
 *
 * Return: command status
 */
int exec(char *input, int *is_separated, int *line_num)
{
    char *buf_ptr;
    char *buf_tmp;
    char **args = NULL;
    int status;

    buf_ptr = input;
    buf_tmp = NULL;

    args = make_array(buf_ptr, ' ', &buf_tmp);

    status = command_manager(args);

    free(args);

    if (*is_separated == FALSE)
        (*line_num)++;

    return status;
}

/**
 * execute_shell - executes commands from the terminal
 *
 * Return: shell exit status
 */
int execute_shell(void)
{
    int is_separated = FALSE;
    int line_num = 1;
    char *input = NULL;
    int exit_status = 0; // Local variable to store exit status
    char *shell_name = _strdup("my_shell");

    environ = array_cpy(environ, list_len(environ, NULL));

    signal(SIGINT, SIG_IGN);

    while (1)
    {
        input = read_input(&is_separated);

        if (input == NULL)
            break;

        char **args = make_array(input, ' ', NULL);
        exit_status = exec(args);
        free(args);

        free(input);

        if (exit_status == EXIT_SHELL)
            break;
    }

    free_array(environ);
    free(shell_name);

    return exit_status;
}
/**
 * main - entry point of the program
 * @ac: number of inputs from main
 * @av: array of inputs from main
 *
 * Return: 0, or another number if desired
 */
int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av)
{
    int exit_status = execute_shell();
    return (exit_status % 256);
}
