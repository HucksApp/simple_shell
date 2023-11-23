#include "shell.h"
/**
 * _copy_path - Copies a portion of the path string specified by
 * start and stop indices.
 * @path: The source path string.
 * @start: The starting index.
 * @stop: The stopping index.
 * Return: A pointer to the copied path.
 */
char *_copy_path(char *path, int start, int stop)
{
	static char buffer[BUFFER_SIZE];
	int iter = 0, index = 0;
	char path_delim = ':';

	for (index = 0, iter = start; iter < stop; iter++)
		if (path[iter] != path_delim)
			buffer[index++] = path[iter];

	/*terminate buffer*/
	buffer[index] = 0;
	return (buffer);
}
/**
 * _is_eXe - Checks if the given path points to a regular file.
 * @path: The path to check.
 * Return: _TRUE if the path points to a regular file, _FALSE otherwise.
 */
int _is_eXe(char *path)
{
	struct stat file_stats;

	if (!path)
		return (_FALSE);
	if (stat(path, &file_stats))
		return (_FALSE);

	if (file_stats.st_mode & S_IFREG)
		return (_TRUE);

	return (_FALSE);
}

/* for futher path handling the shell obj passed as unsed */
/**
 * _get_path - Retrieves the full path for a command.
 * @obj: Pointer to the shell_type object (unused in this function).
 * @paths: The environment variable containing multiple paths.
 * @cmd_name: The name of the command.
 * Return: A pointer to the full path of the command if found, NULL otherwise.
 */
char *_get_path(UNUSED shell_type * obj, char *paths, char *cmd_name)
{
	char *path;
	int is_valid = 0, iter = 0, index = 0;
	char path_delim = ':';

	if (!paths)
		return (NULL);
	is_valid = ((str_len(cmd_name) > 2) && _match_str_path(cmd_name, "./"))
				   ? (_TRUE)
				   : (_FALSE);

	if (is_valid && _is_eXe(cmd_name))
	{
		return (cmd_name);
	}
	for (index = 0; index < 600; iter++)
	{
		if (!paths[iter] || paths[iter] == path_delim)
		{
			path = _copy_path(paths, index, iter);
			if (!*path)
			{
				handleEmptyPath(obj);
				/* path is empty  add new path */
				path = strdup(cmd_name);
			}
			else
			{
				addPathToPath(path, cmd_name);
			}
			if (_is_eXe(path))
				return (path);
			if (!paths[iter])
				break;
			index = iter;
		}
	}
	return (NULL);
}
/**
 * handleEmptyPath - Handles printing aliases when the PATH is empty.
 * @obj: Pointer to the shell_type object.
 */
void handleEmptyPath(shell_type *obj)
{
	string_list_type *aliases = obj->_aliases;

	if (obj->_aliases != NULL)
	{
		while (aliases)
		{
			printf("--alias------[%s]", aliases->_string);
			aliases = aliases->next;
		}
	}
}

/**
 * addPathToPath - Appends a command name to a given path.
 * @path: The path to which the command name is added.
 * @cmdName: The command name to append to the path.
 */
void addPathToPath(char *path, char *cmdName)
{
	_strconcat(path, "/");
	_strconcat(path, cmdName);
}
