#include "shell.h"

int _read_file(char *file_name, char *buffer, ssize_t *file_size)
{
	ssize_t file_descriptor, read_length;
	struct stat file_info;

	*file_size = 0;
	file_descriptor = open(file_name, O_RDONLY);
	if (file_descriptor == SYS_ERROR)
		return (SYS_ERROR);

	if (fstat(file_descriptor, &file_info) == 0)
		/* if file info is filled sucessfully */
		*file_size = file_info.st_size;
	if (*file_size < 2)
		return (_FALSE);

	buffer = malloc(sizeof(char) * ((*file_size) + 1));
	if (!buffer)
		return (_FALSE);

	read_length = read(file_descriptor, buffer, (*file_size));
	/*terminate the buffer*/
	buffer[file_descriptor] = null;

	if (read_length <= 0)
	{
		free(buffer);
		return (_FALSE);
	}
	close(file_descriptor);

	return (_TRUE);
}
