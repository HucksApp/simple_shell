#include "shell.h"
/**
 * _shell_history - Displays the command history.
 * @obj: Pointer to the shell_type object.
 * Return: EXIT_SUCCESS.
 */
int _shell_history(shell_type *obj)
{
	_print_node_strlist(obj->_history);
	return (EXIT_SUCCESS);
}
/**
 * signal_handler - Handles the interrupt signal (SIGINT).
 * @sig: Signal number.
 */
void signal_handler(UNUSED int sig)
{
	_write_string("\n", STDOUT_FILENO);
	_write_string(PROMPT, STDOUT_FILENO);
	_write_char_to_stdeout(BUFFER_FLUSH, STDOUT_FILENO);
}

/**
 * read_buf - Reads information
 * @obj: object struct
 * @buffer: Buffer
 * @iter: Size of the buffer
 * Return: size read
 */
ssize_t read_buf(shell_type *obj, char *buffer, size_t *iter)
{
	ssize_t size = 0;

	if (*iter)
		return (0);
	size = read(obj->_file_descriptor, buffer, BUFFER_SIZE);
	if (size >= 0)
		*iter = size;
	return (size);
}
