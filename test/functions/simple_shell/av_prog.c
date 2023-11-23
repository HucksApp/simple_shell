#include <stdio.h>

int main(int argc, char **av)
{
	int i;

	printf("argc = %d\n", argc);
	for (i = 0; av[i] != NULL; i++)
	{
		printf("%s\n", av[i]);
	}

	return (0);
}
