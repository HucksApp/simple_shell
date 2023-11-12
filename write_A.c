#include "shell.h"

int _buffer_flush(char next_char, int buffer_index, char buffer[])
{
	if (next_char == BUFFER_FLUSH || buffer_index >= BUFFER_SIZE)
		/* if flush signal is passed or buffer is full */
		return (_TRUE);

	/*buffer is useable and inuse, add next_char to buffer*/
	buffer[buffer_index++] = next_char;
	return (_FALSE);
}

int _write_char_to_stderr(char next_char, UNUSED int file_descriptor)
{
	static char buffer_err[BUFFER_SIZE];

	/* static index to keep track of error buffer */
	static int buffer_index;
	int buff_flush;

	buff_flush = _buffer_flush(next_char, buffer_index, buffer_err);
	if (buff_flush)
	{
		write(STDERR_FILENO, buffer_err, buffer_index);
		/* buffer flushed reset buffer index */
		buffer_index = 0;
	}
	return (1);
}

int _write_char_to_fd(char next_char, int file_descriptor)
{

	static char buffer_fd[BUFFER_SIZE];

	/* static index to keep track of fd buffer */
	static int buffer_index;
	int buff_flush;

	buff_flush = _buffer_flush(next_char, buffer_index, buffer_fd);
	if (buff_flush)
	{
		write(file_descriptor, buffer_fd, buffer_index);
		/* buffer flushed reset buffer index */
		buffer_index = 0;
	}

	return (1);
}

int (*which_buffer(int fd))(char c, int fd)
{
	switch (fd)
	{
	case (STDOUT_FILENO):
		return (_write_char_to_stdeout);
	case (STDERR_FILENO):
		return (_write_char_to_stderr);
		/*add more customize function for desired fd */
	default:
		return (_write_char_to_fd);
	}
}

/**
 * _write_string - writes a array of chars in the standard output
 * @str: pointer to the array of chars
 * Return: the number of bytes written or -1
 */

int _write_string(char *str, int file_descriptor)
{
	int print_count;
	int (*fn_write)(char, int);

	if (!str)
		return (_FALSE);

	fn_write = which_buffer(file_descriptor);

	for (print_count = 0; *str != null; str++)
		print_count += fn_write(*str, file_descriptor);
	return (print_count);
}
