#include "shell.h"
/**
 * _shell_exit - Handles the exit command.
 * @obj: Pointer to the shell_type object.
 * Return: EXIT_SIG on exit, _FALSE on failure.
 */
int _shell_exit(shell_type *obj)
{
	int _is_exit;

	if (obj->_tokens[1])
	{
		_is_exit = _etoi(obj->_tokens[1]);
		if (_is_exit == SYS_ERROR)
		{
			obj->_status = 2;
			_print_error_msg(obj, "Illegal number: ");
			_write_string(obj->_tokens[1], STDERR_FILENO);
			_write_char_to_stderr('\n', STDERR_FILENO);
			return (_TRUE);
		}
		obj->_error_num = _etoi(obj->_tokens[1]);
		return (EXIT_SIG);
	}
	obj->_error_num = SYS_ERROR;
	return (EXIT_SIG);
}
/**
 * _shell_help - Displays help messages for built-in commands.
 * @obj: Pointer to the shell_type object.
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int _shell_help(shell_type *obj)
{
	int length, index;
	char *msgs[7] = {NULL};

	msgs[0] = HELP_MSG;
	msgs[1] = HELP_EXIT_MSG;
	msgs[2] = HELP_ENV_MSG;
	msgs[3] = HELP_SETENV_MSG;
	msgs[4] = HELP_UNSETENV_MSG;
	msgs[5] = HELP_CD_MSG;
	msgs[6] = NULL;

	if (obj->_tokens[1] == NULL)
	{

		_write_string(msgs[0] + 6, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	if (obj->_token_count <= 1)
	{
		errno = E2BIG;
		perror(obj->_tokens[1]);
		return (EXIT_FAILURE);
	}

	length = str_len(obj->_tokens[1]);
	for (index = 0; msgs[index] != NULL; index++)
	{

		if (_strcmpr((obj->_tokens[1]), msgs[index], length))
		{
			_write_string(msgs[index] + length + 1, STDOUT_FILENO);
			return (EXIT_SUCCESS);
		}
	}

	errno = EINVAL;
	perror(obj->_tokens[1]);
	return (1);
}
/**
 * _shell_cd - Handles the cd command.
 * @obj: Pointer to the shell_type object.
 * Return: 0 on success, 1 on failure.
 */

int _shell_cd(shell_type *obj)
{
	char *dir = NULL, buffer[1024], *s = getcwd(buffer, 1024);
	int chdir_ret;
	char *prev_old_pwd;

	if (!s)
		_write_string("Error get pwd\n", 1);

	prev_old_pwd = _shell_getenv(obj, "OLDPWD=");
	_set_env(obj, "OLDPWD", buffer);
	if (!obj->_tokens[1])
	{
		dir = _shell_getenv(obj, "HOME=");
		if (!dir)
			chdir_ret = chdir(dir ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (obj->_tokens[1][0] == '-')
	{
		if (!prev_old_pwd)
		{
			_write_string(s, STDOUT_FILENO);
			_write_char_to_stdeout('\n', STDOUT_FILENO);
			return (1);
		}
		_write_string(prev_old_pwd, 1);
		_write_char_to_stdeout('\n', 1);
		chdir_ret = chdir(prev_old_pwd);
	}
	else
		chdir_ret = chdir(obj->_tokens[1]);
	if (chdir_ret == -1)
		printCdErrorMessage(obj);
	getcwd(buffer, 1024);
	_set_env(obj, "PWD", buffer);
	if (dir)
		free(dir);
	free(prev_old_pwd);
	return (0);
}
/**
 * printCdErrorMessage - Prints an error message when changing directory fails.
 * @obj: Pointer to the shell_type object.
 */
void printCdErrorMessage(shell_type *obj)
{
	_print_error_msg(obj, "can't cd to ");
	_write_string(obj->_tokens[1], STDERR_FILENO);
	_write_string("\n", STDERR_FILENO);
}
