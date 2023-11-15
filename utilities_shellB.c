#include "shell.h"

int _is_linked_stream(shell_type *obj, char *buffer, size_t *chain_pos)
{
	size_t index = *chain_pos;

	if (_strcmpr((buffer + index), "||", 2))
	{
		buffer[index] = 0;
		index++;
		obj->_chain_stream_type = CMD_OR;
	}
	else if (_strcmpr((buffer + index), "&&", 2))
	{
		buffer[index] = 0;
		index++;
		obj->_chain_stream_type = CMD_AND;
	}
	else if (_strcmpr((buffer + index), ";", 1))
	{
		buffer[index] = 0;
		index++;
		obj->_chain_stream_type = CMD_CHAIN;
	}
	else
		return (_FALSE);

	*chain_pos = index;
	return (_TRUE);
}

int _swap_tokens(shell_type *obj)
{
	int index;
	char *str;
	string_list_type *node;

	for (index = 0; obj->_tokens[index]; index++)
	{
		if (obj->_tokens[index][0] != '$' || obj->_tokens[index][1])
			continue;

		if (!_strcmpr(obj->_tokens[index], "$?", 2))
		{
			str = _strdupl(_convert_number(obj->_status, 10, 10));
			_swap_string(&(obj->_tokens[index]), str);
			continue;
		}

		if (!_strcmpr(obj->_tokens[index], "$$", 2))
		{
			str = _strdupl(_convert_number(getpid(), 10, 0));
			_swap_string(&(obj->_tokens[index]), str);
			continue;
		}

		node = _match_node_str(obj->_envs, &(obj->_tokens[index][1]), '=');

		if (node)
		{
			str = _strdupl(_strchr_ptr(node->_string, '=') + 1);
			_swap_string(&(obj->_tokens[index]), str);
			continue;
		}
		_swap_string(&(obj->_tokens[index]), _strdupl(""));
	}
	return (EXIT_SUCCESS);
}

void _next_linkedstream(shell_type *obj, char *buffer,
						size_t index, size_t length, size_t *position)
{

	size_t curr_pos = *position;

	if (obj->_chain_stream_type == CMD_OR)
	{
		if (!obj->_status)
		{
			buffer[index] = 0;
			curr_pos = length;
		}
	}

	if (obj->_chain_stream_type == CMD_AND)
	{
		if (obj->_status)
		{ /* terminate buffer */
			buffer[index] = 0;
			curr_pos = length;
		}
	}

	*position = curr_pos;
}

void _run_cmd(shell_type *obj)
{
	char *path = NULL;
	int iter, index, is_mode;

	char *delim = " \t\n";

	obj->_path = obj->_tokens[0];

	if (obj->_read_flag == _TRUE)
	{
		obj->_read_count++;
		obj->_read_flag = _FALSE;
	}

	for (index = 0, iter = 0; obj->_input_args[index]; index++)

		if (!_strchr(obj->_input_args[index], delim))
			/* char is not a delimeter */
			iter++;

	if (!iter)
		return;
	path = _get_path(obj, _shell_getenv(obj, "PATH="), obj->_tokens[0]);

	if (path)
	{
		obj->_path = path;
		_execute(obj);
	}
	else
	{
		is_mode = ((_is_interactive(obj) || _shell_getenv(obj, "PATH=")) ||
				   obj->_tokens[0][0] == '/') &&
						  _is_eXe(obj->_tokens[0])
					  ? (_TRUE)
					  : (_FALSE);

		if (is_mode)
		{
			_execute(obj);
		}

		else if (*(obj->_input_args) != '\n')
		{
			obj->_status = FILE_NOT_FOUND;
			errno = ENOENT;
			perror(obj->_tokens[0]);
		}
	}
}

void _execute(shell_type *obj)
{
	pid_t child_process_id;
	int ret = 0;

	child_process_id = fork();
	if (child_process_id == -1)
	{
		perror(obj->_file_name);
		exit(EXIT_FAILURE);
	}
	if (child_process_id == 0)
	{
		/* inside the child process */

		/* print_str_list(_get_envs(obj));*/
		/*_print_node_strlist(obj->_tokens);START HEREEEE*/
		ret = execve(obj->_path, obj->_tokens, _get_envs(obj));
		free(obj->_path);
		free(obj->_tokens);
		if (ret == SYS_ERROR)
		{

			_garbage_collection(obj, 1);
			perror(obj->_file_name);
			if (errno == EACCES)
				exit(PERMISSION_DENIED);
			exit(EXIT_FAILURE);
		}
	}
	else
	{

		/* inside the parent process */
		wait(&(obj->_status));

		if (WIFEXITED(obj->_status))
		{
			/* child process is finished normally with status */
			obj->_status = WIFEXITED(obj->_status);

			if (obj->_status == PERMISSION_DENIED)
			{
				perror(obj->_file_name);
			}
		}
		else if (WIFSIGNALED(obj->_status))
			/* child process was terminated due to a signal */
			obj->_status = 128 + WTERMSIG(obj->_status);
	}
}
