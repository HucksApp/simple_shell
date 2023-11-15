#include "shell.h"

int _init_sys_envs(shell_type *obj)
{
	string_list_type *node_head = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		_append_node(&node_head, environ[index], 0);
	obj->_envs = node_head;
	return (_TRUE);
}

int _shell_env(shell_type *obj)
{
	print_str_list(obj->_envs);
	return (_TRUE);
}

int _shell_setenv(shell_type *obj)
{
	if (_args_errors(obj, "setenv"))
		return (_FALSE);

	if (_set_env(obj, obj->_tokens[1], obj->_tokens[2]))
		return (_TRUE);
	return (_FALSE);
}

int _shell_unsetenv(shell_type *obj)
{
	int iter;
	if (_args_errors(obj, "unsetenv"))
		return (_FALSE);

	for (iter = 1; iter <= obj->_token_count; iter++)
		_unset_env(obj, obj->_tokens[iter]);

	return (_TRUE);
}

char *_shell_getenv(shell_type *obj, char *name)
{
	string_list_type *node = obj->_envs;

	for (; node; node = node->next)
	{
		/**
		 *  printf("node->_string--> %s\n \n name--> %s\n \n ",
		 *   node->_string, name);
		 */
		if (_match_env(node->_string, name))
		{
			return (((node->_string) + _match_env(node->_string, name) + 1));
		}
	}

	return (NULL);
}
