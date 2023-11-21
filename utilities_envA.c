#include "shell.h"

/**
 * _get_envs - Retrieve the system environment variables as a string array
 * @obj: Shell object
 * Return: The array of environment variables
 */

char **_get_envs(shell_type *obj)
{
	if (!obj->_env || obj->_env_changed)
	{
		obj->_env = _node_to_stringlist(obj->_envs);
		obj->_env_changed = _FALSE;
	}
	return (obj->_env);
}
/**
 * _unset_env - Unset a specific environment variable in the shell
 * @obj: Shell object
 * @var: The name of the variable to unset
 * Return: 1 if successful, 0 if unsuccessful
 */
int _unset_env(shell_type *obj, char *var)
{
	string_list_type *envs_head = obj->_envs;

	size_t index;

	if (!obj || !var)
		return (_FALSE);

	for (index = 0; envs_head != NULL; index++)
	{
		if (_match_env(envs_head->_string, var))
		{

			obj->_env_changed = _remove_node_at(&(obj->_envs), index);
			index = 0;
			envs_head = obj->_envs;
			continue;
		}
		envs_head = envs_head->next;
	}
	return (obj->_env_changed);
}
/**
 * _set_env - Set or update an environment variable in the shell
 * @obj: Shell object
 * @var: The name of the variable to set
 * @var_value: The value to assign to the variable
 * Return: 1 if successful, 0 if unsuccessful
 */
int _set_env(shell_type *obj, char *var, char *var_value)
{
	string_list_type *envs_head = NULL;
	char *buffer_tmp = NULL;
	char *tmp;

	if (!var || !var_value)
		return (_FALSE);

	buffer_tmp = malloc(sizeof(char) * (strlen(var) + strlen(var_value) + 2));
	if (!buffer_tmp)
	{
		return (_FALSE);
	}
	strcpy(buffer_tmp, var);
	strcat(buffer_tmp, "=");
	strcat(buffer_tmp, var_value);
	envs_head = obj->_envs;
	tmp = strdup(buffer_tmp);
	for (; envs_head != NULL; envs_head = envs_head->next)
		if (_match_env(envs_head->_string, var))
		{
			/*env match found*/
			free(envs_head->_string);
			envs_head->_string = strdup(buffer_tmp);
			obj->_env_changed = _TRUE;
			free(buffer_tmp);
			free(tmp);
			return (_TRUE);
		}
	_append_node(&(obj->_envs), tmp, 0);
	free(buffer_tmp);
	free(tmp);
	obj->_env_changed = _TRUE;
	return (_TRUE);
}
/**
 * _match_env - Check if a given environment variable matches the
 * provided string
 * @envs_path: The environment variable to check
 * @env_new: The string to compare with
 * Return: The length of the matching portion if there's a match, 0 if not
 */
int _match_env(char *envs_path, char *env_new)
{
	int is_same;
	int len_to_compare;
	char can_assign = '=';

	if (env_new[str_len(env_new) - 1] == can_assign)
		len_to_compare = str_len(env_new) - 1;
	else
		len_to_compare = str_len(env_new);

	is_same = _strcmpr(envs_path, env_new, len_to_compare);
	if (is_same && envs_path[len_to_compare] == can_assign)
		return (len_to_compare);
	return (_FALSE);
}
/**
 * _match_str - Match two strings and return the position of the
 * match in the first string
 * @bulk: The string to search in
 * @members: The string to search for
 * Return: A pointer to the matched position in the first string,
 *  or NULL if no match
 */
char *_match_str(char *bulk, char *members)
{
	for (; *bulk != '\0'; bulk++, members++)
		if (*members != *bulk)
			return (NULL);
	return ((char *)bulk);
}
