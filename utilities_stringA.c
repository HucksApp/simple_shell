
#include "shell.h"

/**
 * _tokenize - splits a string into tokens using specified delimiters
 * @str: string to tokenize
 * @d: delimiters
 * Return: array of tokens, or NULL on failure
 */

char **_tokenize(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_strchr(str[i], d) && (_strchr(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (_strchr(str[i], d))
			i++;
		k = 0;
		while (!_strchr(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * _strtok - divides strings into words using specified delimiters
 * @str: string to convert
 * @delimiters: word separators array
 * Return: pointer to found position or NULL
 */
char *_strtok(char *str, char *delimiters)
{
	static char *start_token;
	char *end_token = NULL;
	char *ret = NULL;
	int len, iter;

	start_token = NULL;
	if (str != NULL && *str != null)
		start_token = str;
	else if (start_token == NULL)
		return (NULL);
	
	while (*start_token != null && _strchr(*start_token, delimiters))
		start_token++; /* Jump to the non-delimiter character */
	if (*start_token == null)
	{ /* If the string has ended, return null*/
		start_token = NULL;
		return (start_token);
	}
	end_token = start_token;
	/* Find the end of the token*/
	while (*end_token != null && _strchr(*end_token, delimiters) == _FALSE)
		end_token++;
	
	len = end_token - start_token; /* Calculate the length of the token*/
	ret = malloc(sizeof(char) * (len + 1)); /* Allocate memory for the token*/
	if (!ret)
		return (NULL);
	for (iter = 0; iter < len; iter++, start_token++) 
		ret[iter] = *start_token; /* Copy the token to the allocated memory*/
	ret[iter] = null; /* Insert a null terminator at the end of the token*/
	
	if (*end_token == null)
		/* Update start_token to the next position*/
		start_token = NULL;
	else
	{
		*end_token = null;
		start_token = end_token + 1;
	}
	return (ret);
}
/**
 * _strdupl - creates a duplicate string
 * @str: string to duplicate
 * Return: pointer to the new duplicate string
 */

char *_strdupl(char *str)
{
	char *str_dupl;
	int iter, length;

	if (str == NULL)
		return (NULL);

	length = str_len(str) + 1;

	str_dupl = malloc(sizeof(char) * length);

	/* check for memomery allocation */
	if (str_dupl == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	iter = 0;
	while (*str != null)
	{
		str_dupl[iter] = (*str);
		iter++;
		str++;
	}
	str_dupl[iter] = null;
	/* Free heap memomry str_dupl after use */
	return (str_dupl);
}
