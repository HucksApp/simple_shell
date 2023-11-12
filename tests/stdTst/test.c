#include "../shell.h"

// ssize_t write(int fd, const void *buf, size_t count);

int main(int argc UNUSED, char *argv[] UNUSED, char *envp[] UNUSED)
{
	int initz = 1;
	while (initz)
	{

		/* code */
		if (isatty(STDIN_FILENO))
		{
			char cwd[BUFFER_SIZE];
			write(STDOUT_FILENO, "~$", 32);
		}
		else
		{
		}
	}

	return (0);
}
