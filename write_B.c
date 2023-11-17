#include "shell.h"

/**
 * _write_char_to_stdeout - writes a character to the standard output stream
 * @next_char: the character to be written
 * @file_descriptor: UNUSED parameter, not used in the function
 *
 * This function writes the given character to the standard output
 * stream (file descriptor 1).
 * It uses a static buffer to accumulate characters before flushing
 * them to stdout.
 *
 * Return: Always 1
 */
int _write_char_to_stdeout(char next_char, UNUSED int file_descriptor)
{
	static char buffer[BUFFER_SIZE];

	/* static index to keep track of error buffer */
	static int buffer_index;
	int buff_flush;

	buff_flush = _buffer_flush(next_char, &buffer_index, buffer);
	if (buff_flush)
	{

		write(1, buffer, buffer_index);
		/* buffer flushed reset buffer index */
		buffer_index = 0;
	}
	return (1);
}
/**
 * _buffer_remove_comment - removes comments from a buffer
 * @buffer: the character buffer
 *
 * This function removes comments from the buffer. It looks for the
 * '#' character
 * and removes it along with the following characters until the end
 *  of the line.
 * If '#' is at the beginning of the line or after a space, the
 *  entire line is removed.
 */
void _buffer_remove_comment(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != null; index++)

		if (buffer[index] == '#' && (buffer[index - 1] == ' ' || index == 0))
		{
			buffer[index] = null;
			break;
		}
}
