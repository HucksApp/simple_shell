#include "shell.h"

int _init_shell(int argc, char *argv[], shell_type *obj)
{
	int file_descriptor;

	if (argc == 2)
	{
		file_descriptor = open(*(argv + 1), O_RDONLY);

		if (file_descriptor == SYS_ERROR)
		{
			switch (errno)
			{
			case (EACCES):
				exit(PERMISSION_DENIED);
			case (ENOENT):
				_print_file_error(argv);
				exit(FILE_NOT_FOUND);
			default:
				return (EXIT_FAILURE);
			}
		}
		obj->_file_descriptor = file_descriptor;
	}
	return (_FALSE);
}

void _service_start(UNUSED shell_type *obj, UNUSED char *argv[])
{
	/* shell loop */
	/*ssize_t byte_read = 0;
	while (byte_read != SYS_ERROR )
	{

	}
	*/
}

int main(int argc, char *argv[], char *env[])
{
	// char *_prompt = "";
	// shell_type shell_obj = {0, {0}, {0}, {0}};

	shell_type shell_obj = {0};
	shell_type *obj = &shell_obj;

	_init_shell(argc, argv, obj);
	_init_sys_envs(obj, env);
	_read_history(obj);
	_service_start(obj, argv);
	return (EXIT_SUCCESS);
}
