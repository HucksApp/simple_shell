#include "shell.h"

/**
 *  _atoi1 - convert char to int for printing
 * @str: string to convert
 * Return: printable char numbers
 */

int _atoi1(char *str)
{
	int num = 0, sign = 1;

	for (; *str != null; str++)

		/* skip spaces */
		if (*str == ' ')
			continue;
		/*char is a sign*/
		else if (*str == '-')
			sign = -1;

		/*char is a number*/
		else if (_isdigit(*str))
			num = num * 10 + (*str - '0');

		else
			break;

	return (num * sign);
}
/**
 * _etoi - converts a string to an integer
 * @s: the string to convert
 * Return: the converted integer, or -1 if conversion fails
 */
int _etoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++; /* TODO: why does this make main return 255? */
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * _strcat_bybyte - concatenates two strings up to a specified size
 * @dest: string to add to
 * @source: string to add from
 * @size: maximum number of characters to concatenate
 * Return: pointer to the concatenated string
 */

char *_strcat_bybyte(char dest[], char source[], int size)
{
	int index, iter;
	char *result = dest;

	for (index = 0, iter = 0; dest[index] != '\0'; index++)
		;
	for (; source[iter] != '\0' && iter < size; iter++, index++)
		dest[index] = source[iter];

	/* if there are memory space in dest*/
	if (iter < index)
		/* terminate dest*/
		dest[index] = '\0';
	return (result);
}

/**
 * _strcpy_bybyte - copies a string up to a specified size
 * @dest: destination string
 * @source: source string
 * @size: maximum number of characters to copy
 * Return: pointer to the copied string
 */
char *_strcpy_bybyte(char dest[], char source[], int size)
{
	int index, iter;

	char *str = dest;

	for (index = 0; source[index] != '\0' && index < size; index++)
		dest[index] = source[index];

	/* source is less than size */
	if (index < size)
	{
		iter = index;

		for (; iter < size; iter++)
			/*insert null in all*/
			dest[index] = '\0';
	}

	return (str);
}

