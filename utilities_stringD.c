#include "shell.h"

/**
 *  _atoi - convert char to int for printing
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
