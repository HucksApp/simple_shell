#include "shell.h"
/**
 * _count_digits - counts the number of digits in an integer
 * @num: input integer
 * Return: number of digits in the integer
 */
int _count_digits(int num)
{
	int count = 0;

	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}
