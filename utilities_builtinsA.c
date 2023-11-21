#include "shell.h"
/**
 * _builtins_cmds_fn - Find and return the function pointer for
 * a given built-in command.
 * @cmd: The command to search for.
 * Return: Function pointer to the corresponding built-in function
 *  or NULL if not found.
 */
int (*_builtins_cmds_fn(char *cmd))(shell_type * obj)
{
	int iter, length;
	builtins_type builtins_cmds[] = {
		{"exit", _shell_exit},
		{"env", _shell_env},
		{"help", _shell_help},
		{"history", _shell_history},
		{"setenv", _shell_setenv},
		{"unsetenv", _shell_unsetenv},
		{"cd", _shell_cd},
		{"alias", _alias},
		{NULL, NULL}};
	iter = 0;
	length = str_len(cmd);

	while (builtins_cmds[iter]._cmd != NULL)
	{
		/*
		 * printf("strcmp %d \n \n  cmd %s \n \n  len %d \n
		 * \n",_strcmpr(builtins_cmds[iter]._cmd, cmd, length), cmd, length);
		 */
		if (_strcmpr(builtins_cmds[iter]._cmd, cmd, length))
			return (builtins_cmds[iter]._fn);
		iter++;
	}

	return (NULL);
}

/**
 * _find_builtin - Find and execute the built-in command if it exists.
 * @obj: Pointer to the shell_type object.
 * Return: Result of the built-in command execution or -1 if not found.
 */
int _find_builtin(shell_type *obj)
{
	int (*cmd_fn)(shell_type *);
	int found_builtin = -1;

	if (obj->_read_flag == _TRUE)
	{
		obj->_read_count++;
		obj->_read_flag = _FALSE;
	}
	cmd_fn = _builtins_cmds_fn(obj->_tokens[0]);

	if (cmd_fn != NULL)
		found_builtin = cmd_fn(obj);

	return (found_builtin);
}
