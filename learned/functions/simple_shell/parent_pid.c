#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("Parent Process PID: %d\n", getppid());
	printf("Current Process PID: %d\n", getpid());

		return (0);
}
