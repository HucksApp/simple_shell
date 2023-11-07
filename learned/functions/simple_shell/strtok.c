#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[] = "bin bash fav guy";
	const char *delim = " ";
	char *res;

	res = strtok(str, delim);

	while (res != NULL)
	{
		printf("%s\n", res);
		res = strtok(NULL, delim);
	}

	return (0);
}
