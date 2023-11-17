#include "shell.h"
/**
 * _strcpy - copies a string from source to destination
 * @destination: the destination string
 * @source: the source string
 * Return: pointer to the destination string
 */
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
/**
 * _atoi - converts a string to an integer
 * @str: the string to convert
 * Return: the converted integer, or SYS_ERROR if conversion fails
 */
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
/**
 * _match_str_path - checks if two strings match
 * @strs: the first string
 * @str: the second string
 * Return: a pointer to the location in strs where the strings
 * differ, or NULL if they match
 */

char *_match_str_path(char *strs, char *str)
{
	/* this is a second match fn if strcmp is not available */
	for (; *strs; str++, strs++)
		if (*str != *strs)
			return (NULL);
	return (strs);
}
/**
 * _swap_string - frees the memory of the old string and assigns the new string
 * @old: pointer to the old string
 * @new: the new string
 * Return: _TRUE if successful
 */
int _swap_string(char **old, char *new)
{
	_free(*old);
	*old = new;
	return (_TRUE);
}

/**
 * _convert_number - converts a number to a string in the specified base
 * @num: the number to convert
 * @base: the base of the conversion
 * @flags: flags for the conversion (e.g., CONVERT_LOWERCASE)
 * Return: pointer to the converted string
 */
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
