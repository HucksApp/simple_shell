#include "shell.h"

void _print_file_error(char *argv[])
{
	_write_string(argv[0], STDERR_FILENO);
	_write_string(": 0: Can't open ", STDERR_FILENO);
	_write_string(argv[1], STDERR_FILENO);
	_write_char_to_stderr('\n', STDERR_FILENO);
	_write_char_to_stderr(BUFFER_FLUSH, STDERR_FILENO);
}

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
		_write_string(((node->_string) ? (node->_string) : ("(nil)")), STDOUT_FILENO);
		_write_string("\n", STDOUT_FILENO);
	}
	return (count);
}

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
