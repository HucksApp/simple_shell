#include "shell.h"
/**
 * _patch_alias - Updates the command with the alias value if available.
 * @obj: Pointer to the shell_type object.
 * Return: _TRUE on success, _FALSE on failure.
 */
int _patch_alias(shell_type *obj)
{
	int iter, assign_index;
	char *ch;
	string_list_type *node;

	for (iter = 0; iter < MAX_ALIAS; iter++)
	{
		node = _match_node_str(obj->_aliases, obj->_tokens[0], '=');

		if (!node)
			return (_FALSE);

		free(obj->_tokens[0]);
		assign_index = _strchr('=', node->_string);
		ch = node->_string;

		if (!assign_index)
			return (_FALSE);

		ch = _strdupl(ch + (assign_index + 1));
		if (!ch)
			return (_FALSE);
		obj->_tokens[0] = ch;
	}
	return (_TRUE);
}
