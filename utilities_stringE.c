#include "shell.h"
/**
 * _reverse_str - reverses a string
 * @str: string to reverse
 */
void _reverse_str(char *str)
{
	int frm_start, frm_end;
	char temp_char;

	if (str != NULL)
	{

		frm_start = 0;

		/* jump null char at end with -1 */
		frm_end = str_len(str) - 1;

		while (frm_start < frm_end)
		{
			/* swap characters */
			temp_char = str[frm_start];
			str[frm_start] = str[frm_end];
			str[frm_end] = temp_char;
			frm_start++;
			frm_end--;
		}
	}
}
/**
 * _strchr_ptr - searches for a specified character in a string
 * @str: string to search in
 * @c: character to search for
 * Return: pointer at position if found, NULL if not found
 */
char *_strchr_ptr(char *str, int c)
{
	unsigned int len = 1;

	while (*str != null && *str != c)
	{
		str++;
		len++;
	}
	/* return position of character or NULL */
	return ((*str == c) ? str : NULL);
}

/**
 * _strchr - searches for a specified character in a string
 * @c: character to search for
 * @str: string to search in
 * Return: position of character if found, 0 if not found
 */

int _strchr(int c, const char *str)
{
	unsigned int len = 1;

	while (*str != null && *str != c)
	{
		str++;
		len++;
	}
	/* return position of character or NULL */
	return ((*str == c) ? len : _FALSE);
}

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}
