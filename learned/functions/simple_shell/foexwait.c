#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	char *argv[] = {"/bin/ls", "-l", ".", NULL};
	pid_t child_p;
	int status;
	int i, numofchil = 3;

	for (i = 0; i < numofchil; i++)
	{
		child_p = fork();
		if (child_p == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("exec failed");
				return (-1);
			}
		}
		else if (child_p > 0)
		{
			wait(&status);
			printf("\n-----------------child finished ------------\n");
			sleep(3);
			wait(&status);
		}
	}
	return (0);
}
