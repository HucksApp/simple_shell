#include "shell.h"
/**
 * _build_history - Builds the history linked list with command lines.
 * @obj: Pointer to the shell_type object.
 * @buffer: The command line to be added to the history.
 * @line_count: The line count of the command line.
 * Return: _TRUE on success, _FALSE on failure.
 */

int _build_history(shell_type *obj, char *buffer, int line_count)
{
	string_list_type *new_node = NULL;

	if (obj->_history)
		/* if history is initialized */
		new_node = obj->_history;

	_append_node(&(new_node), buffer, line_count);

	if (!(obj->_history))
		/* if history is uninitialized  new node is head history*/
		obj->_history = new_node;

	return (_TRUE);
}
/**
 * _get_history_file - Generates the full path of the history file.
 * @obj: Pointer to the shell_type object.
 * Return: A pointer to the generated history file path or NULL on failure.
 */

char *_get_history_file(shell_type *obj)
{
	char *buffer, *dir;

	dir = _shell_getenv(obj, "HOME=");
	if (!dir)
		return (NULL);

	buffer = malloc(sizeof(char) * (str_len(dir) + str_len(HISTORY_FILE) + 2));
	if (buffer == NULL)
		return (NULL);

	/* sample_look of $HISTFILE   /Users/username/.simple_shell_history */
	/* add null to buffer to create the space before file name */

	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strconcat(buffer, "/");
	_strconcat(buffer, HISTORY_FILE);
	free(dir);
	return (buffer);
}
/**
 * _history_indexing - Indexes the history linked list.
 * @obj: Pointer to the shell_type object.
 * Return: The count of nodes in the history linked list.
 */
int _history_indexing(shell_type *obj)
{

	int index;
	string_list_type *node = obj->_history;

	for (index = 0; node; index++, node = node->next)
		node->_num = index;

	/* count is the index of the last node*/
	obj->_history_count = index;
	return (obj->_history_count);
}
/**
 * _write_history - Writes the history linked list to the history file.
 * @obj: Pointer to the shell_type object.
 * Return: _TRUE on success, SYS_ERROR on failure.
 */

int _write_history(shell_type *obj)
{
	ssize_t file_descriptor;
	char *file_name;
	string_list_type *current_node;

	file_name = _get_history_file(obj);
	if (!file_name)
		return (SYS_ERROR);

	file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);

	if (file_descriptor == SYS_ERROR)
		return (SYS_ERROR);

	current_node = obj->_history;
	for (; current_node != NULL; current_node = current_node->next)
	{
		_write_string(current_node->_string, file_descriptor);
		_write_char_to_fd('\n', file_descriptor);
	}
	_write_char_to_fd(BUFFER_FLUSH, file_descriptor);
	close(file_descriptor);
	return (_TRUE);
}
/**
 * _read_history - Reads the history file and populates the history
 *  linked list.
 * @obj: Pointer to the shell_type object.
 * Return: The count of nodes in the history linked list on success,
 *  SYS_ERROR on failure.
 */
int _read_history(shell_type *obj)
{
	char *buffer = NULL, *file_name;
	int index, nxt_build_index = 0, f_read = 0, read_line_counter = 0;
	ssize_t file_size = 0;

	file_name = _get_history_file(obj);

	if (!file_name)
		return (_FALSE);
	buffer = _read_file(file_name, &f_read, &file_size);

	if (f_read)
	{

		for (index = 0; index < file_size; index++)
		{
			if (buffer[index] == '\n')
			{
				/* end of cmd or end of line, terminate buffer*/
				buffer[index] = 0;
				read_line_counter++;

				/* move buffer index to next position and build */
				_build_history(obj, (buffer + nxt_build_index), read_line_counter);

				nxt_build_index = index + 1;
			}
		}
		/* last history is not yet termainated by newline '\n' */
		if (nxt_build_index != index)
			/*last build index is not the last cmd */
			_build_history(obj, (buffer + nxt_build_index), read_line_counter++);

		obj->_history_count = read_line_counter;
		free(buffer);
		_history_size_monitor(obj);
		free(file_name);
		return (obj->_history_count);
	}
	free(file_name);
	return (SYS_ERROR);
}
