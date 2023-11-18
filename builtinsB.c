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

