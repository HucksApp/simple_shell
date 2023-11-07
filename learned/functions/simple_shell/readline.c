#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	size_t bufsize = 0;
	char *inputbuffer = NULL;
	ssize_t charead;

	while (1)
	{
		printf("$[Royalty]: ");
		charead = getline(&inputbuffer, &bufsize, stdin);
		if (charead != -1)
		{
			inputbuffer[charead - 1] = '\0';
			printf("%s\n", inputbuffer);
		}
		if (charead == -1)
		{
			printf("exited loop\n");
			break;
		}
	}

	free(inputbuffer);
	return (0);
}