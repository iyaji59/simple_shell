#include "shell.h"
#include "2-strtok.c"
#include "2-getline.c"
#include "2-getenv.c"
#include "cd.c"
#include "alias.c"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

char exit_status_variable[16];
void replace_variable(char *arg, const char *variable, const char *replacement) {
    char *variable_ptr = strstr(arg, variable);
    if (variable_ptr != NULL)
    {
        char new_arg[MAX_COMMAND_LENGTH];
        strncpy(new_arg, arg, variable_ptr - arg);
        new_arg[variable_ptr - arg] = '\0';
        strncat(new_arg, replacement, sizeof(new_arg) - strlen(new_arg) - 1);
        strcat(new_arg, variable_ptr + strlen(variable));
        strcpy(arg, new_arg);
    }
}
int parse_arguments(char *command, char **args);
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
char *getpid_str() {
    static char pid_str[16];
    sprintf(pid_str, "%d", getpid());
    return pid_str;
}
void execute_command(char *command, char **args) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        // Replace variable in each argument
        for (int i = 0; args[i] != NULL; i++) {
            replace_variable(args[i], "$?", exit_status_variable);
            replace_variable(args[i], "$$", getpid_str());
        }

        char *envp[] = { NULL }; // Empty environment for execve

        execve(command, args, environ);

        // execve only returns if an error occurs
        perror("Command execution failed");
        exit(1);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        sprintf(exit_status_variable, "%d", WEXITSTATUS(status));
    }
}
void execute_commands(char *command, char **args) {
    char *semicolon = strchr(command, ';');

    if (semicolon != NULL) {
        char *token = my_strtok(command, ";");

        while (token != NULL) {
            char *trimmed_command = strtok(token, " \t");
            if (trimmed_command != NULL) {
                char *trimmed_args[MAX_ARGS];
                int arg_count = parse_arguments(trimmed_command, trimmed_args);
                execute_command(trimmed_command, trimmed_args);
            }
=======
>>>>>>> 8868df231eb2cbfdc1c7fb728015fb682fdfcb85

int status = 0;

int line_num = 1;

char *shell_name = NULL;

/**
 * main - entry point of terminal
 * @ac: args count
 * @av: args value
 * Return: success or failure
 */
int main(__attribute__((unused))int ac, char **av)
{
	int bytes_read;
	int is_separated = FALSE;
	int i;
	size_t buf_size = 1;
	char *buf = NULL;
	char *buf_ptr;
	char *buf_tmp;
	char **args = NULL;

	shell_name = _strdup(*av);
	environ = array_cpy(environ, list_len(environ, NULL));
	signal(SIGINT, SIG_IGN);
	buf = malloc(1);
	if (buf == NULL)
		exit(EXIT_FAILURE);

	while (1)
	{
		if (is_separated == FALSE)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(STDOUT_FILENO, "my_shell$ ", 10);

			bytes_read = getline(&buf, &buf_size, stdin);

			if (bytes_read == -1)
				break;
			if (bytes_read == 1)
			{
				line_num++;
				continue;
			}
			buf[bytes_read - 1] = '\0';
			buf = input_san(buf, &buf_size);
			if (buf_size == 0)
			{
				line_num++;
				continue;
			}
			buf_ptr = buf;
		}
		else
			buf_ptr = buf_tmp;

		buf_tmp = NULL;
		args = make_array(buf_ptr, ' ', &buf_tmp);
		if (buf_tmp != NULL)
			is_separated = TRUE;
		else
			is_separated = FALSE;

		i = command_manager(args);

		free(args);

		if (is_separated == FALSE)
			line_num++;

		if (i == EXIT_SHELL)
			break;
	}
	free(buf);
	alias_func(NULL, TRUE);
	free_array(environ);
	free(shell_name);

	return (status % 256);
}
