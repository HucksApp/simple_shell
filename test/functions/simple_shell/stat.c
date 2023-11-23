#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char *path_env = getenv("PATH");
	char *path_copy = strdup(path_env);
	char *path_token = strtok(path_copy, ":");
	int found = 0;
	int i;

	if (argc < 2)
	{
		printf("Usage: %s filename ...\n", argv[0]);
		return 1;
	}

	if (path_env == NULL)
	{
		printf("Error: PATH environment variable not found\n");
		return 1;
	}

	while (path_token != NULL)
	{
		for (i = 1; i < argc; ++i)
		{
			char *file_path = malloc(strlen(path_token) + strlen("/") + strlen(argv[i]) + 1);
			sprintf(file_path, "%s/%s", path_token, argv[i]);

			if (access(file_path, F_OK) == 0)
			{
				printf("%s: %s\n", argv[i], file_path);
				found = 1;
			}

			free(file_path);
		}

		path_token = strtok(NULL, ":");
	}

	free(path_copy);

	if (!found)
	{
		printf("No matching files found in PATH.\n");
	}

	return 0;
}
