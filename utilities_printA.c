#include "shell.h"

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
