#include "shell.h"

int _is_interactive(shell_type *obj)
{
	/*check if file in use is a terminal file*/
	return ((isatty(STDIN_FILENO) &&
			 isatty(STDOUT_FILENO) && obj->_file_descriptor <= 2)
				? (_TRUE)
				: (_FALSE));
}
