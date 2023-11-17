#include "shell.h"
/**
 * _print_file_error - Prints a file opening error message to standard error.
 * @argv: Argument vector containing the program name and file name.
 */

void _print_file_error(char *argv[])
{
	_write_string(argv[0], STDERR_FILENO);
	_write_string(": 0: Can't open ", STDERR_FILENO);
	_write_string(argv[1], STDERR_FILENO);
	_write_char_to_stderr('\n', STDERR_FILENO);
	_write_char_to_stderr(BUFFER_FLUSH, STDERR_FILENO);
}
/**
 * _print_node_strlist - Prints the contents of a string list along
 *  with their indices.
 * @head: Head of the string list.
 * Return: Number of nodes in the list.
 */
size_t _print_node_strlist(string_list_type *head)
{
	size_t count;
	string_list_type *node = head;

	for (count = 0; node; count++, node = node->next)
	{
		/* print string or nil if string is empty */
		_write_string(_convert_number(node->_num, 10, 0), STDOUT_FILENO);
		_write_char_to_stdeout(':', STDOUT_FILENO);
		_write_char_to_stdeout(' ', STDOUT_FILENO);
		_write_string(((node->_string) ? (node->_string)
									   : ("(nil)")),
					  STDOUT_FILENO);
		_write_string("\n", STDOUT_FILENO);
	}
	return (count);
}
/**
 * _print_error_msg - Prints an error message to
 * standard error, including file name, line number,
 * command, and the specific error message.
 * @obj: Pointer to the shell_type object.
 * @error_msg: The specific error message.
 */
void _print_error_msg(shell_type *obj, char *error_msg)
{
	if (obj->_file_name != NULL)
	{
		_write_string(obj->_file_name, STDERR_FILENO);
		_write_string(": ", STDERR_FILENO);
	}
	_print_decimal(obj->_read_count, STDERR_FILENO);
	_write_string(": ", STDERR_FILENO);
	if (obj->_tokens[0] != NULL)
	{
		_write_string(obj->_tokens[0], STDERR_FILENO);
		_write_string(": ", STDERR_FILENO);
	}
	_write_string(error_msg, STDERR_FILENO);
}

/**
 * _print_decimal - Prints a decimal number to the specified file descriptor.
 * @num: The number to print.
 * @file_descriptor: The file descriptor to print to.
 * Return: Number of characters printed, or -1 on error.
 */
int _print_decimal(unsigned int num, int file_descriptor)
{
	int i, count = 0, size;
	unsigned int _abs;
	char *digits = NULL;

	int (*_write_char)(char, int) = which_buffer(file_descriptor);

	(void)_write_char;
	_abs = num;

	size = _count_digits(_abs);
	digits = malloc(sizeof(char) * size + 1);
	if (digits == NULL)
		return (-1);
	for (i = size - 1; i >= 0; i--, _abs /= 10, count++)
		digits[i] = ('0' + (_abs % 10));
	digits[size] = '\0';

	_write_string(digits, file_descriptor);
	free(digits);
	return (count);
}
/**
 * print_str_list - Prints the strings in a string list to standard output.
 * @head: Head of the string list.
 * Return: Number of nodes in the list.
 */
size_t print_str_list(string_list_type *head)
{
	size_t index;
	string_list_type *node = head;

	for (index = 0; node; index++)
	{
		_write_string(node->_string ? node->_string : "(nil)", 1);
		_write_string("\n", 1);
		node = node->next;
	}
	return (index);
}
