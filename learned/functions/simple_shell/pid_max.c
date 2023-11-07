#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	__pid_t my_pid;
	__pid_t MAX_PID = 0;
	int i;

	for (i = 0; i < 10000; i++)
	{

		my_pid = getpid();
		printf("%u --\n", my_pid);
		if (my_pid > MAX_PID)
			MAX_PID = my_pid;
		sleep(1);
	}
	printf("%u\n", MAX_PID);

	return (0);
}