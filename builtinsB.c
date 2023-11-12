#include "shell.h"

int _shell_history(shell_type *obj)
{
	_print_node_strlist(obj->_history);
	return (EXIT_SUCCESS);
}
