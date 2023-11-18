#include "shell.h"



/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int _print_alias(string_list_type *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr_ptr(node->_string, '=');
		
		for (a = node->_string; a <= p; a++)
		{
			
			_write_char_to_stdeout(*a, STDOUT_FILENO);
		}
			
		_write_char_to_stdeout('\'',STDOUT_FILENO);
		_write_string(p + 1, STDOUT_FILENO);
		_write_string("'\n'", STDOUT_FILENO);
		return (0);
	}
	return (1);
}

