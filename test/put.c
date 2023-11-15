#include "shell.h"

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	
	static char buffer[BUFFER_SIZE];
    static int index;
	
	if (c == BUFFER_FLUSH || index >= BUFFER_SIZE)
	{
		write(2, buffer, index);
		index = 0;
		
	}
	if (c != BUFFER_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int file_descriptor)
{
	
	static char buf[BUFFER_SIZE];
    static int index;

	if (c == BUFFER_FLUSH || index >= BUFFER_SIZE)
	{
		write(file_descriptor, buf, index);
		index = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[index++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int file_descriptor)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += _putfd(*str++, file_descriptor);
	}
	return (index);
}

