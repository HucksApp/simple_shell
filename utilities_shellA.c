#include "shell.h"

void _destroy_sh_obj(shell_type *obj, int total)
{
	_free_string_list(obj->_tokens);
	obj->_tokens = NULL;
	obj->_path = NULL;

	if (total)
	{
		if (obj->_envs)
			_free_strlistnode(obj->_envs);

		if (obj->_aliases)
			_free_strlistnode(obj->_envs);

		if (obj->_history)
			_free_strlistnode(obj->_history);

		if (obj->_cmd_chain)
			_free_str_in_str((void **)obj->_cmd_chain);

		if (obj->_env)
		{
			_free_string_list(obj->_env);
			obj->_env = NULL;
		}

		if (obj->_file_descriptor > 2)
			close(obj->_file_descriptor);

		_write_char_to_stdeout(BUFFER_FLUSH, STDOUT_FILENO);
	}
}

int _shell_refresh(shell_type *obj)
{
	obj->_tokens = NULL;
	obj->_token_count = 0;
	obj->_path = NULL;
	obj->_input_args = NULL;
	return ((obj->_tokens || obj->_token_count ||
			 obj->_path || obj->_input_args)
				? (_FALSE)
				: (_TRUE));
}

void _create_shell_token(shell_type *obj)
{
	obj->_input_args = malloc(sizeof(char *) * 2);
	if (obj->_input_args)
	{
		obj->_tokens[0] = _strdupl(obj->_input_args);
		obj->_tokens[1] = NULL;
	}
}

char **_tokenize(char *str, char *deli)
{
	int length, list_index;
	char **token_list;
	char *token;

	length = str_len(str);
	token_list = malloc(sizeof(char) * length + 1);

	if (str == NULL || str[0] == 0 || token_list == NULL)
		return (NULL);
	if (!deli)
		/*default delimeter*/
		deli = " ";

	token = _strtok(str, deli);
	for (list_index = 0; token != NULL; list_index++)
	{
		token = _strtok(NULL, deli);
		token_list[list_index] = token;
		if (!token_list[list_index])
		{
			_free(token_list[list_index]);
		}
	}

	token_list[list_index] = NULL;

	if (!token_list)
	{
		free(token_list);
		return (NULL);
	}
	return (token_list);
}

void _set_shell_obj(shell_type *obj, char *argv[])
{
	int iter = 0;
	char delimeter[] = " \t";

	obj->_file_name = argv[0];

	/* There is inputs */
	if (obj->_input_args)
	{
		obj->_tokens = _tokenize(obj->_input_args, delimeter);

		if (!obj->_tokens)
		{
			obj->_tokens = malloc(sizeof(char *) * 2);
			if (obj->_tokens)
			{
				obj->_tokens[0] = _strdupl(obj->_input_args);
				obj->_tokens[1] = NULL;
			}
		}
		/*count tokens*/
		for (iter = 0; obj->_tokens && obj->_tokens[iter]; iter++)
			;
		obj->_token_count = iter;
		_patch_alias(obj);
		_swap_tokens(obj);
	}
}
