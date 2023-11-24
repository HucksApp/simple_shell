#include "shell.h"
/**
 * _create_shell_obj - Initializes the shell_type object with default values.
 * @obj: Pointer to the shell_type object.
 */

void _init_shell_obj(shell_type *obj)
{
	obj->_tokens = NULL;
	obj->_env = NULL;
	obj->_input_args = NULL;
	obj->_path = NULL;
	obj->_file_name = NULL;
	obj->_cmd_chain = NULL;
	obj->_read_count = 0;
	obj->_read_flag = _FALSE;
	obj->_aliases = NULL;
	obj->_envs = NULL;
	obj->_history = NULL;
	obj->_history_count = 0;
	obj->_token_count = 0;
	obj->_file_descriptor = 0;
	obj->_status = 0;
	obj->_env_changed = 0;
	obj->_error_num = 0;
	obj->_chain_stream_type = 0;
}
/**
 * main - Entry point for the shell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 * Return: 0 on success, 1 on error.
 */
int main(int argc, char **argv)
{
	shell_type obj[] = {0};
	int file_descriptor = 2;

	_init_shell_obj(obj);
	if (argc == 2)
	{
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == SYS_ERROR)
		{
			if (errno == EACCES)
				exit(PERMISSION_DENIED);
			if (errno == ENOENT)
			{
				_print_file_error(argv);
				exit(FILE_NOT_FOUND);
			}
			return (EXIT_FAILURE);
		}
		obj->_file_descriptor = file_descriptor;
	}
	_init_sys_envs(obj);
	_read_history(obj);
	_start_process(obj, argv);
	return (EXIT_SUCCESS);
}
