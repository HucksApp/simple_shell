#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	__pid_t child_pid;
	__pid_t c_pid;
	int status;
	int num_children = 3;
	int i;

	for (i = 0; i < num_children; ++i)
		child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		c_pid = getpid();
		printf("(%d)Wait for me, wait for me\n", c_pid);
		sleep(3);
	}
	else
	{
		wait(&status);
		printf("(%d)Oh, it's all better now\n", getppid());
	}
	return (0);
}