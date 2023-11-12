#include "shell.h"

/**
 * _strconcat - concatenate two string
 * @source: string to add from
 * @dest: string to add to
 * Return: pointer to contenated string
 */

char *_strconcat(char dest[], char source[])
{
	int dest_len, source_len, iter, length;
	char *concat_str;

	if (dest == NULL)
		dest = "";
	if (source == NULL)
		source = "";

	dest_len = str_len(source);
	source_len = str_len(dest);

	length = dest_len + source_len + 1;
	concat_str = malloc(sizeof(char) * length);

	/*check for memory allocation error*/
	if (concat_str == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (iter = 0; *source != null; source++, iter++)
		concat_str[iter] = *source;

	for (; *dest != null; dest++, iter++)
		concat_str[iter] = *dest;

	_free(source);
	_free(dest);

	concat_str[iter] = null;

	/* heap memmory in use remember to free */
	return (concat_str);
}

/**
 * _strcmpr - compare two string
 * @str1: string to compare 1
 * @str2: string to compare 2
 * @size: string to add to
 * Return: TRUE 1 or FALSE 0
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
 * _isalpha - Verifies the char c is an alphabet
 * @ch: Char
 * Return: 1 if c is a digit, 0 if false
 */

int _isalpha(int ch)
{
	/*its between a and z or A and Z ascii value */
	if ((ch >= 'a' && ch <= 'Z') || (ch >= 'A' && ch <= 'Z'))
		return (_TRUE);
	return (_FALSE);
}

/**
 * _isdigit - Verifies the char c is a digit
 * @ch: Char
 * Return: 1 if c is a digit, 0 if false
 */
int _isdigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (_TRUE);
	return (_FALSE);
}

/**
 * str_len - find string length
 * @str: string
 * Return: string length
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
