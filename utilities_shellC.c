#include "shell.h"

/**
 * _is_interactive - checks if the shell is running in an interactive mode
 * @obj: pointer to the shell_type object
 * Return: _TRUE (1) if interactive, _FALSE (0) otherwise
 */
int _is_interactive(shell_type *obj)
{
	/*check if file in use is a terminal file*/
	return ((isatty(STDIN_FILENO) &&
			 isatty(STDOUT_FILENO) && obj->_file_descriptor <= 2)
				? (_TRUE)
				: (_FALSE));
}
