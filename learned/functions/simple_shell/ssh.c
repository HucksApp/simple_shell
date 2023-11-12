#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

extern char **environ;
void readinput(void);

void showrez(char *argv[])
{
	pid_t child;
	int status;
	char *path = getenv("PATH");
	char *path_copy;
	char *dir;
	char full_path[256];

	if (!path)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[0]);
		if (access(full_path, F_OK) == 0)
		{
			child = fork();
			if (child == 0)
			{
				execve(full_path, argv, environ);
			}
			wait(&status);
			free(path_copy);
			readinput();
			return;
		}
		dir = strtok(NULL, ":");
	}
	printf("./shell: No such file or directory\n");
	free(path_copy);
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
				/*printf("%s\n", str);*/
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
