#include <unistd.h>
#include "shell.h"
#define BUFFER_SIZE 128
/**
 * read_buffer - read input from user
 * @buffer: where to store the input
 * Return: bufsize
 */
static ssize_t read_buffer(char *buffer)
{
	ssize_t buf_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);

	if (buf_size <= 0)
		return (-1);
	return (buf_size);
}
/**
 * copy_to_lineptr - copy input to array
 * @lineptr: array to copy to
 * @n: array size
 * @buffer: where to store the array
 * @buf_pos: buffer position
 * @buf_size: buffer size
 * Return: success
 */
static ssize_t copy_to_lineptr(char **lineptr, size_t *n, char *buffer,
		ssize_t *buf_pos, ssize_t buf_size)
{
	ssize_t bytes_read = 0;

	while (*buf_pos < buf_size)
	{
		if (bytes_read >= *n - 1)
		{
			*n *= 2;
			char *temp = (char *) realloc(*lineptr, *n);

			if (temp == NULL)
				return (-1);
			*lineptr = temp;
		}
		(*lineptr)[bytes_read] = buffer[*buf_pos];
		bytes_read++;
		(*buf_pos)++;
		if ((*lineptr)[bytes_read - 1] == '\n')
		{
			(*lineptr)[bytes_read] = '\0';
			return (bytes_read);
		}
	}
	return (bytes_read);
}
/**
 * my_getline - read input from user
 * @n: length of input
 * @lineptr: array to read into
 * Return: success
 */
ssize_t my_getline(char **lineptr, size_t *n)
{
	if (lineptr == NULL || n == NULL)
		return (-1);
	if (*lineptr == NULL || *n == 0)
	{
		*n = BUFFER_SIZE;
		*lineptr = (char *) malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	static char buffer[BUFFER_SIZE];
	static ssize_t buf_pos;
	static ssize_t buf_size;

	ssize_t bytes_read = 0;

	if (buf_pos == buf_size)
	{
		buf_pos = 0;
		buf_size = read_buffer(buffer);
		if (buf_size <= 0)
			return (-1);
	}
	ssize_t byt = copy_to_lineptr(lineptr, n, buffer, &buf_pos, buf_size);

	if (byt == -1)
	{
		free(*lineptr);
		*lineptr = NULL;
		return (-1);
	}
	return (bytes_read + byt);
}
