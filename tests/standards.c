
#include "shell.h"
/*
ssize_t my_getline(char **line, size_t *len, int fd);
char **line: A pointer to a pointer to the line read.
size_t *len: A pointer to the length of the allocated buffer.
int fd: The file descriptor from which to read (e.g., 0 for stdin)

*/

char *_getline()
{
	char *buffer_ptr = NULL;
	ssize_t bytes_read, line_size = 0, i = 0;
	ssize_t buffer_size = BUFFER_SIZE;

	// int buffer_size = BUFFER_SIZE;

	// char buff[BUFFER_SIZE] = {'\0'};
	// static char *array_commands[10] = {NULL};
	// static char array_operators[10] = {'\0'};
	// ssize_t bytes_read, i = 0;
}

ssize_t _read_buffer(shell_type *obj)
{
	ssize_t bytes_read = 0;
}

int _is_interactive_mode(shell_type *obj)
{
	/*check if file in use is a terminal file*/
	(isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && obj->_file_descriptor <= 2) ? (_TRUE) : (_FALSE);
}

void _reset(shell_type *obj)
{
}