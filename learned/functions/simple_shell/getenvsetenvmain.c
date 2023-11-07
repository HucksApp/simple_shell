#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;
static char **custom_environ = NULL;

char *_getenv(const char *name)
{
	const char *delim = "=";
	char *res = NULL;
	char *current_var = NULL;
	char **env = environ;
	char *token;

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

void initialize_custom_environ()
{
	int i = 0;
	int j;

	/* Count the number of environment variables */
	while (environ[i] != NULL)
	{
		i++;
	}

	/* Allocate memory for custom_environ */
	custom_environ = malloc((i + 1) * sizeof(char *));
	if (custom_environ == NULL)
		exit(EXIT_FAILURE);

	/* Duplicate and store environment variables in custom_environ */
	for (j = 0; j < i; ++j)
	{
		custom_environ[j] = strdup(environ[j]);
		if (custom_environ[j] == NULL)
			exit(EXIT_FAILURE);
	}

	/* Null-terminate the custom_environ array */
	custom_environ[i] = NULL;
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
	len = strlen(name) + strlen("=") + strlen(value) + 1;

	/* Allocate memory for the new environment variable */
	new_var = malloc(len);
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

int main(int argc, char **av, char **env)
{
	char **env2 = environ;
	int i = 0;
	(void)argc;
	(void)av;
	(void)env;
	(void)i;
	(void)env2;

	initialize_custom_environ();

	_setenv("HELLO", "this is not it", 1);
	printf("%s\n----------------------\n", _getenv("HELLO"));

	while (custom_environ[i] != NULL)
	{
		printf("%s\n", custom_environ[i]);
		i++;
	}
	i = 0;
	while (custom_environ[i] != NULL)
	{
		free(custom_environ[i]);
		i++;
	}
	free(custom_environ);
	return (0);
}
