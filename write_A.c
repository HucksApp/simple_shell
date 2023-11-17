#include "shell.h"
/**
 * _buffer_flush - flushes the buffer or adds a character to it
 * @next_char: the character to be added or the flush signal
 * @buffer_index: pointer to the index of the buffer
 * @buffer: the character buffer
 *
 * This function flushes the buffer if the flush signal is passed or
 * if the buffer
 * is already full. If the buffer is usable and in use, it adds
 *  the next character
 * to the buffer.
 *
 * Return: _TRUE if flush signal is passed or buffer is full, _FALSE otherwise
 */
int _buffer_flush(char next_char, int *buffer_index, char buffer[])
{
	if (next_char == BUFFER_FLUSH || *buffer_index >= BUFFER_SIZE)
		/* if flush signal is passed or buffer is full */
		return (_TRUE);

	/*buffer is useable and inuse, add next_char to buffer*/
	if (next_char != BUFFER_FLUSH)
	{
		buffer[(*buffer_index)++] = next_char;
		return (_FALSE);
	}

	return (_FALSE);
}
/**
 * _write_char_to_stderr - writes a character to the standard error stream
 * @next_char: the character to be written
 * @file_descriptor: UNUSED parameter, not used in the function
 *
 * This function writes the given character to the standard
 * error stream (file descriptor 2).
 * It uses a static buffer to accumulate characters before
 * flushing them to stderr.
 *
 * Return: Always 1
 */
int _write_char_to_stderr(char next_char, UNUSED int file_descriptor)
{
	static char buffer[BUFFER_SIZE];

	/* static index to keep track of error buffer */
	static int buffer_index;
	int buff_flush;

	buff_flush = _buffer_flush(next_char, &buffer_index, buffer);
	if (buff_flush)
	{
		write(2, buffer, buffer_index);
		/* buffer flushed reset buffer index */
		buffer_index = 0;
	}
	return (1);
}
/**
 * _write_char_to_fd - writes a character to the specified file descriptor
 * @next_char: the character to be written
 * @file_descriptor: the file descriptor to write to
 *
 * This function writes the given character to the specified file descriptor.
 * It uses a static buffer to accumulate characters before flushing
 * them to the file descriptor.
 *
 * Return: Always 1
 */
int _write_char_to_fd(char next_char, int file_descriptor)
{

	static char buffer_fd[BUFFER_SIZE];

	/* static index to keep track of fd buffer */
	static int buffer_index;
	int buff_flush;

	buff_flush = _buffer_flush(next_char, &buffer_index, buffer_fd);
	if (buff_flush)
	{
		/**
		 *printf(" stdout %d\n  buffer %s\n  buffer_index %d",
		 *	   STDERR_FILENO, buffer_fd, buffer_index);
		 */
		write(file_descriptor, buffer_fd, buffer_index);
		/* buffer flushed reset buffer index */
		buffer_index = 0;
	}

	return (1);
}
/**
 * which_buffer - returns the appropriate buffer function based on
 * file descriptor
 * @fd: the file descriptor
 *
 * This function takes a file descriptor as input and returns a
 *  function pointer
 * to the corresponding buffer function for that file descriptor.
 *
 * Return: Pointer to the buffer function
 */
int (*which_buffer(int fd))(char c, int fd)
{
	switch (fd)
	{
	case (STDOUT_FILENO):
		return (_write_char_to_stdeout);
	case (STDERR_FILENO):
		return (_write_char_to_stderr);
		/* add more customize function for desired fd */
	default:
		return (_write_char_to_fd);
	}
}
/**
 * _write_string - writes a string to the specified file descriptor
 * @str: the string to be written
 * @file_descriptor: the file descriptor to write to
 *
 * This function writes the given string to the specified file descriptor
 * using the appropriate buffer function determined by the file descriptor.
 *
 * Return: The number of characters written
 */
int _write_string(char *str, int file_descriptor)
{
	size_t print_count, iter;
	int (*fn_write)(char, int);

	if (!str)
		return (_FALSE);

	fn_write = which_buffer(file_descriptor);

	for (print_count = 0, iter = 0; str[print_count] != null; iter++)
	{
		print_count += fn_write(str[print_count], file_descriptor);
	}
	return (print_count);
}
