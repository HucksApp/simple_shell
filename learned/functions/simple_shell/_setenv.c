#include <stdlib.h>
#include <string.h>
#include "shell.h"

extern char **environ;
static char **custom_environ = NULL;

void initialize_custom_environ(shell_type *shell_info)
{
	env_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	shell_info->_env = node;
	return (0);
}
int _setenv(const char *name, const char *value, int overwrite)
{
	char *existing_value;
	int len;
	char *new_var;
	int i;
	int num_vars;

	/*Check if the variable already exists*/
	existing_value = _getenv(name);

	/*If the variable exists and overwrite is not allowed, do nothing */
	if (existing_value != NULL && !overwrite)
	{
		free(existing_value);
		return (0);
	}

	/* Calculate the length needed for the new environment variable */
	len = strlen(name) + strlen(value) + 2;

	/* Allocate memory for the new environment variable */
	new_var = malloc(len * sizeof(char));
	if (new_var == NULL)
	{
		free(existing_value);
		return (-1);
	}

	/* Create the new environment variable manually */
	strcpy(new_var, name);
	strcat(new_var, "=");
	strcat(new_var, value);

	/* Replace the old environment variable with the new one */
	if (existing_value != NULL && overwrite)
	{
		for (i = 0; custom_environ[i] != NULL; ++i)
		{
			if (strncmp(custom_environ[i], name, strlen(name)) == 0)
			{
				free(custom_environ[i]);
				custom_environ[i] = new_var;
				free(existing_value);
				return (0);
			}
		}
	}
	else
	{
		/* If the variable doesn't exist, add the new one to the environment */
		num_vars = 0;
		while (custom_environ[num_vars] != NULL)
		{
			++num_vars;
		}

		custom_environ = realloc(custom_environ, (num_vars + 2) * sizeof(char *));
		if (custom_environ == NULL)
		{
			free(new_var);
			free(existing_value);
			return (-1);
		}

		custom_environ[num_vars] = new_var;
		custom_environ[num_vars + 1] = NULL;
		free(existing_value);
		return (0);
	}
	free(new_var);
	free(existing_value);
	return (-1);
}
