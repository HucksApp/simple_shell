#include "shell.h"

char *_strcpy(char *destination, char *source)
{
	int index = 0;
	if (!destination && source)
		return (source);

	else if (destination && !source)
		return (destination);

	for (index = 0; source[index] != null; index++)
		destination[index] = source[index];

	/*Null-terminate the destination string*/
	destination[index] = null;
	return (destination);
}







int _atoi(char *str)
{
	int iter = 0, sign = 1;
	unsigned long int ret;

	/* skip the leading space */
	while (str[iter] == ' ')
		iter++;

	/* if its signed */
	if (str[iter] == '-' || str[iter] == '+')
		/* update the sign var */
		sign = (str[iter++] == '-') ? -1 : 1;

	while (str[iter] != '\0')
	{

		if (_isdigit(str[iter]))
		{
			/*if value is greater than max allowed*/
			if (ret > INT_MAX / 10 || (ret == INT_MAX / 10 && str[iter] - '0' > 7))
				return (SYS_ERROR);
			/* return((sign == 1)? INT_MAX : INT_MIN);*/

			ret = (ret * 10) + (str[iter++] - '0');
		}
		else
			return (SYS_ERROR);
	}

	return (ret * sign);
}

char *_match_str_path(char *strs, char *str)
{
	/* this is a second match fn if strcmp is not available */
	for (; *strs; str++, strs++)
		if (*str != *strs)
			return (NULL);
	return (strs);
}

int _swap_string(char **old, char *new)
{
	_free(*old);
	*old = new;
	return (_TRUE);
}

char *_convert_number(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];

	char sign = null;
	char *ptr;
	unsigned long int unsiged_num = num;

	char SMALL[] = "0123456789abcdef";
	char CAP[] = "0123456789ABCDEF";

	if ((flags & CONVERT_LOWERCASE) == 0 && num < 0)
	{
		unsiged_num = -num;
		sign = '-';
	}
	ptr = &buffer[49];
	*ptr = null;
	arr = ((flags & CONVERT_LOWERCASE) ? (SMALL) : (CAP));

	while (unsiged_num != 0)
	{
		*(--ptr) = arr[unsiged_num % base];
		unsiged_num /= base;
	}

	if (sign)
		*(--ptr) = sign;

	return (ptr);
}
