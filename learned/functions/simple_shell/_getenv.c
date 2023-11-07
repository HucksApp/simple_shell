#include <string.h>
#include <stdio.h>
#include <stdlib.h>
extern char **environ;

char *_getenv(const char *name)
{
	const char *delim = "=";
	char *res = NULL;
	char *current_var = NULL;
	char **env = environ;
	char *token;

	if (name == NULL)
		return (NULL);
	/*go through all the env variables*/
	while (*env != NULL)
	{
		/*store current variable in current_var*/
		if (current_var != NULL)
			free(current_var);
		current_var = strdup(*env);
		token = strtok(current_var, delim);
		/*tokenize and get the second part of the variable after "=" */
		if (token != NULL && strcmp(token, name) == 0)
		{
			res = strdup(strtok(NULL, delim));
			break;
		}

		env++;
	}
	if (current_var != NULL)
		free(current_var);
	return (res);
}
