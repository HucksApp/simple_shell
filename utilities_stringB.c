#include "shell.h"

/**
 * _strconcat - concatenates two strings
 * @source: string to add from
 * @dest: string to add to
 * Return: pointer to concatenated string
 */

char *_strconcat(char dest[], char source[])
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*source)
		*dest++ = *source++;
	*dest = *source;
	return (ret);
}

/**
 * _strcmpr - compares two strings up to a specified size
 * @str1: first string to compare
 * @str2: second string to compare
 * @size: maximum number of characters to compare
 * Return: _TRUE (1) if strings match, _FALSE (0) otherwise
 */
int _strcmpr(char *str1, char *str2, int size)
{
	int iter;
	/* if both string is NULL */
	if (str1 == NULL && str2 == NULL)
		return (_TRUE);

	/* if One string is NULL*/
	if (str1 == NULL || str2 == NULL)
		return (_FALSE);

	if (!size)
	{
		/* if length is different */
		if (str_len(str1) != str_len(str2))
			return (_FALSE);

		for (; *str1 != null && *str2 != null; str1++, str2++)
			/*if one character is different */
			if (*str1 != *str2)
				return (_FALSE);
		return (_TRUE);
	}
	else
	{
		for (iter = 0; iter < size; iter++, str1++, str2++)
			if (*str1 != *str2)
				return (_FALSE);
		return (_TRUE);
	}
}
/**
 * _isalpha - checks if a character is an alphabet letter
 * @ch: the character
 * Return: _TRUE (1) if ch is an alphabet letter, _FALSE (0) otherwise
 */
int _isalpha(int ch)
{
	/*its between a and z or A and Z ascii value */
	if ((ch >= 'a' && ch <= 'Z') || (ch >= 'A' && ch <= 'Z'))
		return (_TRUE);
	return (_FALSE);
}

/**
 * _isdigit - checks if a character is a digit
 * @ch: the character
 * Return: _TRUE (1) if ch is a digit, _FALSE (0) otherwise
 */

int _isdigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (_TRUE);
	return (_FALSE);
}
/**
 * str_len - finds the length of a string
 * @str: the string
 * Return: the length of the string
 */

int str_len(char *str)
{
	int length = 0;

	if (str == NULL)
		return (0);

	while (*str != null)
	{
		length++;
		str++;
	}
	return (length);
}
