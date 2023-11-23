#include "shell.h"
/**
 * _run_cmd - runs the command specified in the shell_type object
 * @obj: pointer to the shell_type object
 */

void _run_cmd(shell_type *obj)
{
	char *path = NULL;
	int iter;
	char *temp_path;
	char *file_name = NULL;
	char *delim = " \t\n";

	obj->_path = obj->_tokens[0];

	if (obj->_read_flag == _TRUE)
	{
		obj->_read_count++;
		obj->_read_flag = _FALSE;
	}

	iter = countNonDelimiters(obj, delim);

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
		handleNonexistentPath(obj, temp_path, file_name);
	}
	if (temp_path)
		free(temp_path);
}

/**
 * countNonDelimiters - Counts non-delimiter characters in a string.
 * @obj: Pointer to the shell_type object.
 * @delim: Delimiter characters.
 * Return: Number of non-delimiter characters.
 */
int countNonDelimiters(shell_type *obj, char *delim)
{
	int nonDelimiterCount = 0;
	int index;

	for (index = 0, nonDelimiterCount = 0; obj->_input_args[index]; index++)

		if (!_strchr(obj->_input_args[index], delim))
			/* char is not a delimeter */
			nonDelimiterCount++;
	return (nonDelimiterCount);
}
/**
 * handleNonexistentPath - Handles non-existent command paths.
 * @obj: Pointer to the shell_type object.
 * @temp_path: Temporary PATH variable.
 * @file_name: Name of the script or executable.
 */
void handleNonexistentPath(shell_type *obj, char *temp_path, char *file_name)
{
	int is_mode;

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
