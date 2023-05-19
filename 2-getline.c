#include <unistd.h>
#include "shell.h"
ssize_t my_getline(char **lineptr, size_t *n) {
    // Check if lineptr or n is NULL
    if (lineptr == NULL || n == NULL) {
        return -1;
    }

    // Set the initial buffer size if not already allocated
    if (*lineptr == NULL || *n == 0) {
        *n = 128;  // You can adjust the initial buffer size as needed
        *lineptr = (char*) malloc(*n);
        if (*lineptr == NULL) {
            return -1;  // Memory allocation failed
        }
    }

    // Static variables to hold buffer and its state
    static char buffer[128];  // Buffer size, should match the initial size of *lineptr
    static ssize_t buf_pos = 0;  // Position in buffer
    static ssize_t buf_size = 0;  // Number of characters in buffer

    ssize_t bytes_read = 0;  // Number of bytes read from read() system call

    // Check if buffer is empty, refill it if necessary
    if (buf_pos == buf_size) {
        buf_pos = 0;
        buf_size = read(STDIN_FILENO, buffer, sizeof(buffer));
        if (buf_size <= 0) {
            return -1;  // Error or end of file
        }
    }

    // Copy characters from buffer to lineptr
    while (buf_pos < buf_size) {
        // Increase lineptr buffer size if necessary
        if (bytes_read >= *n - 1) {
            *n *= 2;
            char *temp = (char*) realloc(*lineptr, *n);
            if (temp == NULL) {
                return -1;  // Memory allocation failed
            }
            *lineptr = temp;
        }

        // Copy character from buffer to lineptr
        (*lineptr)[bytes_read] = buffer[buf_pos];
        bytes_read++;
        buf_pos++;

        // Check for end of line
        if ((*lineptr)[bytes_read - 1] == '\n') {
            // Null-terminate the line
            (*lineptr)[bytes_read] = '\0';
            return bytes_read;
        }
    }

    // If the buffer is exhausted but no end of line found, call my_getline recursively
    ssize_t bytes_read_next = my_getline(lineptr, n);
    if (bytes_read_next == -1) {
        return -1;  // Error or end of file
    }

    return bytes_read + bytes_read_next;
}
