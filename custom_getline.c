#include "shell.h"
#define INITIAL_BUFFER_SIZE 1024

/**
 * initialize_line_buffer - Initialize the line buffer with an initial size.
 * @lineptr: Pointer to the line buffer.
 * @n: Pointer to the size of the line buffer.
 * Return: 0 on success, -1 on memory allocation error.
 */
int initialize_line_buffer(char **lineptr, size_t *n)
{
	int result = 0;
	*n = INITIAL_BUFFER_SIZE;
	*lineptr = (char *)malloc(*n);

	if (*lineptr == NULL)
	{
		perror("Memory allocation error");
		result = (-1);
	}
	return (result);
}

/**
 * read_line - Read a line from the given file descriptor into the line buffer.
 * @lineptr: A pointer to the line buffer.
 * @n: A pointer to the size of the line buffer.
 * @file_d: The file descriptor to read from.
 *
 * Return: The number of characters read, including the newline character,
 *         -1 on memory allocation error, or -1 on EOF.
 */
ssize_t readline(char **lineptr, size_t *n, int file_d)
{
	ssize_t bytes_read;
	char *line;

	if (*lineptr == NULL || *n == 0)
	{
		*n = INITIAL_BUFFER_SIZE;
		*lineptr = (char *)malloc(*n);

		if (*lineptr == NULL)
		{
			return (-1);
		}
	}

	bytes_read = 0;
	line = *lineptr;

	while (1)
	{
		char c, *new_line;
		ssize_t res;

		res = read(file_d, &c, 1);

		if (res == -1)
		{
			perror("read error");
			free(line);
			*lineptr = NULL;

			return (-1);
		}
		else if (res == 0)
		{
			if (bytes_read == 0)
			{
				return (-1);
			}
			break;
		}
		line[bytes_read++] = c;
		if (c == '\n')
		{
			break;
		}
		if (bytes_read >= (ssize_t)(*n))
		{
			*n *= 2;
			new_line = (char *)realloc(line, *n);

			if (new_line == NULL)
				return (-1);
			line = new_line;
			*lineptr = line;
		}
	}
	line[bytes_read] = '\0';

	return (bytes_read);
}
/**
 * get_line - Read a line from the stream into the line buffer.
 * @lineptr: Pointer to the line buffer.
 * @n: Pointer to the size of the line buffer.
 * @str: File stream to read from.
 *
 * Return: The number of characters read, including the newline character,
 *         -1 on memory allocation error, or -1 on EOF.
 *
 * This function reads a line from the provided file stream into the line buffer.
 * It dynamically reallocates memory for the buffer as needed and returns the
 * number of characters read, -1 on memory allocation error, or -1 on EOF.
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *str)
{
	if (*lineptr != NULL)
	{
		/**
		 * free previous memory
		 */
		free(*lineptr);
		/**
		 * Reset the pointer
		 */
		*lineptr = NULL;
		*n = 0;
	}
	return (readline(lineptr, n, fileno(str)));
}
