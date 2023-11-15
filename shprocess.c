#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int _start_process(shell_type *obj, UNUSED char **av)
{
	ssize_t read_line = 0;
	int builtin_ret = 0;

	while (read_line != SYS_ERROR && builtin_ret != EXIT_SIG)
	{
		_shell_refresh(obj);
		if (_is_interactive(obj))
		{
			_write_string(PROMPT, STDOUT_FILENO);
		}
		_write_char_to_stderr(BUFFER_FLUSH, STDERR_FILENO);

		read_line = _get_input(obj);

		if (read_line != SYS_ERROR)
		{

			_set_shell_obj(obj, av);
			builtin_ret = _find_builtin(obj);
			if (builtin_ret == SYS_ERROR)
			{
				_run_cmd(obj);
				debugger1(obj->_tokens);
			}
		}
		else if (_is_interactive(obj))
		{

			_write_char_to_stdeout('\n', 1);
		}
		_garbage_collection(obj, 0);
	}
	_write_history(obj);

	_garbage_collection(obj, 1);
	if (!_is_interactive(obj) && obj->_status)
		exit(obj->_status);
	if (builtin_ret == EXIT_SIG)
	{
		if (obj->_error_num == SYS_ERROR)
			exit(obj->_status);
		exit(obj->_error_num);
	}

	return (builtin_ret);
}