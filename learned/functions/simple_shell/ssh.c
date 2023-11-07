#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

void readinput(void);

void showrez(char *argv[])
{
	pid_t child;
	int status;

	child = fork();
	if (child == 0)
	{
		execve(argv[0], argv, NULL);
	}
	wait(&status);
	readinput();
}
void readinput(void)
{
	char *buff = NULL;
	size_t size;
	char *str;
	char *argv[1];
	int i = 0;
	ssize_t readchar;
	char *delim = " ";

	while (1)
	{
		printf("Simple_Shell$ ");
		i = 0;

		readchar = getline(&buff, &size, stdin);
		if (readchar != -1)
		{
			buff[readchar - 1] = '\0';
			str = strtok(buff, delim);

			while (str != NULL)
			{
				argv[i++] = str;
				printf("%s\n", str);
				str = strtok(NULL, " ");
			}
			while (argv[i] != NULL)
			{
				argv[i++] = NULL;
			}
			showrez(argv);
		}
		else if (readchar == -1)
		{
			printf("\n");
			break;
		}
		free(buff);
	}
}

int main(void)
{
	readinput();
	return (0);
}
