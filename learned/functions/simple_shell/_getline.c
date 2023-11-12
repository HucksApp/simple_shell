#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char *line;
	int c;
	ssize_t index = 0;
	int buffer_size = 128;

	line = (char *)malloc((buffer_size + 1) * sizeof(char));
	if (line == NULL)
		exit(EXIT_FAILURE);

	while ((c = fgetc(stream)) != EOF && c != '\n')
	{

		if (index >= buffer_size - 1)
		{
			buffer_size *= 2;
			line = (char *)realloc(line, (buffer_size + 1) * sizeof(char));
			if (line == NULL)
			{
				exit(EXIT_FAILURE);
			}
		}
		line[index++] = (char)c;
	}
	line[index] = '\0';

	*lineptr = line;
	*n = index;

	if (c == EOF && index == 0)
	{
		free(line);
		return (-1);
	}
	return (index);
}

int main()
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	printf("Enter a line of text: ");
	read = _getline(&line, &len, stdin);

	if (read != -1)
	{
		printf("Line read: %s %ld", line, strlen(line));
	}
	else
	{
		printf("Error reading the line.\n");
	}

	free(line);

	return (0);
}