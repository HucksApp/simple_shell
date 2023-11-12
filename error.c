#include "shell.h"

int _args_errors(shell_type *obj, char *cmd_type)
{
	;
	if (_strcmpr(cmd_type, "setenv", 0))
	{
		if (obj->_token_count != 3)
		{
			errno = E2BIG;
			perror((obj->_file_name) ? (obj->_file_name) : (obj->_tokens[1]));
			//_write_string("Incorrect number of arguements\n", STDERR_FILENO);
			return (_TRUE);
		}
		return (_FALSE);
	}
	else if (_strcmpr(cmd_type, "unsetenv", 0))
	{
		if (obj->_token_count <= 1)
		{

			errno = E2BIG;
			perror((obj->_file_name) ? (obj->_file_name) : (obj->_tokens[1]));
			//_write_string("Too few arguements.\n", STDERR_FILENO);
			return (_TRUE);
		}
	}
	return (_FALSE);
}
