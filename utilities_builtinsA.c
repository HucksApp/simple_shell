#include "shell.h"

int (*_builtins_cmds_fn(char *cmd))(shell_type *obj)
{
	int iter, length;
	builtins_type builtins_cmds[] =
		{
			{"exit", _shell_exit},
			{"env", _shell_env},
			{"help", _shell_help},
			{"history", _shell_history},
			{"setenv", _shell_setenv},
			{"unsetenv", _shell_unsetenv},
			{"cd", _shell_cd},
			/*{"alias", _myalias},*/
			{NULL, NULL}};
	iter = 0;
	length = str_len(cmd);
	while (builtins_cmds[iter]._cmd != NULL)
	{
		if (_strcmpr(builtins_cmds[iter]._cmd, cmd, length))
			return (builtins_cmds[iter]._fn);
	}

	return (NULL);
}

int _find_builtin(shell_type *obj)
{
	int (*cmd_fn)(shell_type *);
	int found_builtin = -1;

	cmd_fn = _builtins_cmds_fn(obj->_tokens[0]);
	if (cmd_fn != NULL)
		found_builtin = cmd_fn(obj);

	return (found_builtin);
}
