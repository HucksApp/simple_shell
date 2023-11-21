#include "shell.h"

/**
 **_strchrt - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchrt(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * _update_buffer - buffers chained commands
 * @obj: shell obj
 * @buffer: address of buffer
 * @length: address of len value
 *
 * Return: bytes read
 */

ssize_t _update_buffer(shell_type *obj, char **buffer, size_t *length)
{
	ssize_t read_line = 0;
	size_t len_p = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, signal_handler);

		read_line = _getline(obj, buffer, &len_p);
		if (read_line > 0)
		{
			if ((*buffer)[read_line - 1] == '\n')
			{
				(*buffer)[read_line - 1] = '\0'; /* remove trailing newline */
				read_line--;
			}
			obj->_read_flag = _TRUE;
			_buffer_remove_comment(*buffer);
			_build_history(obj, *buffer, obj->_history_count++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*length = read_line;
				obj->_cmd_chain = buffer;
			}
		}
	}
	return (read_line);
}

/**
 * _getinput - gets a line minus the newline
 * @obj: parameter struct
 * Return: bytes read
 */
ssize_t _getinput(shell_type *obj)
{
	static char *buffer;
	static size_t index, iter, len;
	ssize_t read_line = 0;
	char **buf_p = &(obj->_input_args), *p;

	_write_char_to_stdeout(BUFFER_FLUSH, STDOUT_FILENO);
	read_line = _update_buffer(obj, &buffer, &len);
	if (read_line == -1)
		return (-1);
	if (len)
	{
		iter = index;
		p = buffer + index;

		_next_linkedstream(obj, buffer, index, len, &iter);
		while (iter < len)
		{
			if (_is_linked_stream(obj, buffer, &iter))
				break;
			iter++;
		}

		index = iter + 1;
		if (index >= len)
		{
			index = len = 0;
			obj->_chain_stream_type = CMD_NUL;
		}

		*buf_p = p;
		return (str_len(p));
	}

	*buf_p = buffer;
	return (read_line);
}

/**
 * _getline - gets the next line of input from standard input
 * @obj:  shell obj
 * @ptr: address of pointer to buffer
 * @length: size of preallocated ptr buffer
 *
 * Return: s
 */
int _getline(shell_type *obj, char **ptr, size_t *length)
{
	static char buf[BUFFER_SIZE];
	static size_t iter, len;
	size_t size;
	ssize_t r = 0, s = 0;
	char *p = NULL, *pointer_n = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (iter == len)
		iter = len = 0;

	r = _read_buffer(obj, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchrt(buf + iter, '\n');
	size = c ? 1 + (unsigned int)(c - buf) : len;
	pointer_n = _realloc(p, s, s ? s + size : size + 1);
	if (!pointer_n)
		return (p ? free(p), -1 : -1);

	if (s)
		_strcat_bybyte(pointer_n, buf + iter, size - iter);
	else
		_strcpy_bybyte(pointer_n, buf + iter, size - iter + 1);

	s += size - iter;
	iter = size;
	p = pointer_n;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
