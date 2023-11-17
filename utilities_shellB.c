#include "shell.h"
/**
 * _is_linked_stream - checks if the current position in the buffer
 *  indicates a linked stream
 * @obj: pointer to the shell_type object
 * @buffer: the input buffer
 * @chain_pos: pointer to the current position in the buffer
 * Return: _TRUE (1) if linked stream found, _FALSE (0) otherwise
 */
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
/**
 * _swap_tokens - swaps special tokens like "$?" and "$$" with their
 * corresponding values
 * @obj: pointer to the shell_type object
 * Return: EXIT_SUCCESS on success, -1 on failure
 */
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
/**
 * _next_linkedstream - updates the current position based
 * on the type of linked stream
 * @obj: pointer to the shell_type object
 * @buffer: the input buffer
 * @index: current position in the buffer
 * @length: length of the buffer
 * @position: pointer to the current position in the buffer
 */
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
			buffer[index] = '\0';
			curr_pos = length;
		}
	}

	*position = curr_pos;
}
/**
 * _run_cmd - runs the command specified in the shell_type object
 * @obj: pointer to the shell_type object
 */

void _run_cmd(shell_type *obj)
{
	char *path = NULL;
	int iter, index, is_mode;
	char *temp_path;
	char *file_name;

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
	temp_path = _shell_getenv(obj, "PATH=");
	path = _get_path(obj, temp_path, obj->_tokens[0]);
	if (path)
	{
		obj->_path = path;

		_execute(obj);
	}
	else
	{
		is_mode = ((_is_interactive(obj) || temp_path) ||
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
			if (temp_path == NULL)
				temp_path = _shell_getenv(obj, "PATH1=");
			if (temp_path == NULL)
			{
				file_name = basename(obj->_file_name);
				fprintf(stderr, "./%s: %d: %s: not found\n",
						file_name, obj->_read_count, obj->_tokens[0]);
			}
			else
			{
				fprintf(stderr, "%s: %d: %s: not found\n",
						obj->_file_name, obj->_read_count, obj->_tokens[0]);
			}
		}
	}
	if (temp_path)
		free(temp_path);
}

/**
 * _execute - executes the specified command in a child process
 * @obj: pointer to the shell_type object
 */
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
			obj->_status = WEXITSTATUS(obj->_status);
			if (obj->_status == PERMISSION_DENIED)
			{
				perror(obj->_file_name);
			}
		}
		else if (WIFSIGNALED(obj->_status))
		{
			/* child process was terminated due to a signal */
			obj->_status = 128 + WTERMSIG(obj->_status);
		}
	}
}
