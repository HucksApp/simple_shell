#include "shell.h"

/**
 * remove_comments - Replaces the first instance of
 *  '#' with '\0' if it is preceded by a space.
 * @buf: Address of the string to modify.
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

/**
 * input_buf - buffers chained commands
 * @obj: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(shell_type *obj, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, signal_handler);

		r = _get_line(obj, buf, &len_p);
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			obj->_read_flag = _TRUE;
			remove_comments(*buf);
			_build_history(obj, *buf, obj->_history_count++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				obj->_cmd_chain = buf;
			}
		}
	}
	return (r);
}

/**
 * _get_input - Gets a line minus the newline.
 * @obj: Parameter struct.
 * Return: Bytes read.
 */
ssize_t _get_input(shell_type *obj)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(obj->_input_args), *p;

	_write_char_to_stdeout(BUFFER_FLUSH, STDOUT_FILENO);
	r = input_buf(obj, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i;		 /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		_next_linkedstream(obj, buf, i, len, &j);
		while (j < len) /* iterate to semicolon or end */
		{
			if (_is_linked_stream(obj, buf, &j))
				break;
			j++;
		}

		i = j + 1;	  /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			obj->_chain_stream_type = CMD_NUL;
		}

		*buf_p = p;			 /* pass back pointer to current command position */
		return (str_len(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r);	  /* return length of buffer from _getline() */
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @obj: Parameter struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 * Return: s.
 */
int _get_line(shell_type *obj, char **ptr, size_t *length)
{
	static char buf[BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(obj, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchrt(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
