#include "shell.h"
/**
 * _init_sys_envs - Initializes system environment variables for the shell.
 * @obj: Pointer to the shell_type object.
 * Return: _TRUE on success, _FALSE on failure.
 */
int _init_sys_envs(shell_type *obj)
{
	string_list_type *node_head = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		_append_node(&node_head, environ[index], 0);
	obj->_envs = node_head;
	return (_TRUE);
}

/**
 * _shell_env - Displays the current environment variables.
 * @obj: Pointer to the shell_type object.
 * Return: _TRUE.
 */
int _shell_env(shell_type *obj)
{
	print_str_list(obj->_envs);
	return (_TRUE);
}
/**
 * _shell_setenv - Sets a new environment variable or updates an existing one.
 * @obj: Pointer to the shell_type object.
 * Return: _TRUE if successful, _FALSE if an error occurs.
 */
int _shell_setenv(shell_type *obj)
{
	if (_args_errors(obj, "setenv"))
		return (_FALSE);

	if (_set_env(obj, obj->_tokens[1], obj->_tokens[2]))
		return (_TRUE);
	return (_FALSE);
}
/**
 * _shell_unsetenv - Unsets one or more environment variables.
 * @obj: Pointer to the shell_type object.
 * Return: _TRUE if successful, _FALSE if an error occurs.
 */

int _shell_unsetenv(shell_type *obj)
{
	int iter;

	if (_args_errors(obj, "unsetenv"))
		return (_FALSE);

	for (iter = 1; iter <= obj->_token_count; iter++)
		_unset_env(obj, obj->_tokens[iter]);

	return (_TRUE);
}
/**
 * _shell_getenv - Gets the value of a specified environment variable.
 * @obj: Pointer to the shell_type object.
 * @name: The name of the environment variable.
 * Return: A string containing the value of the environment
 * variable, or NULL if not found.
 */
char *_shell_getenv(shell_type *obj, char *name)
{
	string_list_type *node = obj->_envs;
	char *env_value;

	for (; node; node = node->next)
	{
		/**
		 *  printf("node->_string--> %s\n \n name--> %s\n \n ",
		 *   node->_string, name);
		 */
		if (_match_env(node->_string, name))
		{
			env_value = malloc(strlen(node->_string) -
							   _match_env(node->_string, name) + 1);
			if (env_value == NULL)
				return (NULL);
			strcpy(env_value, (node->_string) + _match_env(node->_string, name) + 1);
			return (env_value);
		}
	}

	return (NULL);
}
