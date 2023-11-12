#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
extern char **environ;

char *_getenv(const char *name, shell_type *shell_info)
{
	const char *delim = "=";
	char *res = NULL;
	char *current_var = NULL;
	env_t *env = shell_info->env;
	char *token;

	if (name == NULL)
		return (NULL);
	/*go through all the env variables*/
	while (env != NULL)
	{
		/*store current variable in current_var*/
		if (current_var != NULL)
			free(current_var);
		current_var = strdup(env->str);
		token = strtok(current_var, delim);
		/*tokenize and get the second part of the variable after "=" */
		if (token != NULL && strcmp(token, name) == 0)
		{
			res = strdup(strtok(NULL, delim));
			break;
		}

		env = env->next;
	}
	if (current_var != NULL)
		free(current_var);
	return (res);
}
env_t *duplicate_env_list(const env_t *head)
{
	env_t *new_head = NULL;
	const env_t *current_node = head;

	if (head == NULL)
		return (NULL);

	while (current_node != NULL)
	{
		add_node_end(&new_head, current_node->str);
		current_node = current_node->next;
	}

	return (new_head);
}
int _getenv_index(const char *name, shell_type *shell_info)
{
	env_t *env = duplicate_env_list(shell_info->env);
	char *token;
	size_t i = 0;
	int index = -1;

	if (name == NULL)
	{
		free_env(&env);
		return (-1);
	}
	/*go through all the env variables*/
	while (env != NULL)
	{
		token = strtok(env->str, "=");
		/*tokenize and get the second part of the variable after "=" */
		if (token != NULL && strcmp(token, name) == 0)
		{
			index = i;
			break;
		}

		env = env->next;
		i++;
	}
	free_env(&env);
	return (index);
}
/**
 * print_env - prints all the elements of a environment list.
 * @h: pointer to head
 * Return: the size of the list
 */
size_t print_env(const env_t *h)
{
	int n = 0;

	while (h != NULL)
	{
		printf("%s\n", h->str);
		h = h->next;
		n++;
	}
	return (n);
}
void initialize_custom_environ(shell_type *shell_info)
{
	env_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i]);
	shell_info->env = node;
}
int _setenv(const char *name,
			const char *value, int overwrite, shell_type *shell_info)
{
	/*implement shelltype use, allong with getenv*/
	int index = _getenv_index(name, shell_info);
	env_t *node = shell_info->env;
	char *env_var;

	size_t env_var_len = strlen(name) + strlen(value) + 2;

	env_var = malloc(env_var_len);
	if (env_var == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return (0);
	}

	strcpy(env_var, name);
	strcat(env_var, "=");
	strcat(env_var, value);

	if (index == -1)
	{
		add_node_end(&node, env_var);
	}
	else
	{
		if (overwrite)
		{
			delete_node_at_index(&node, index);
			add_node_end(&node, env_var);
		}
		else
		{
			return (0);
		}
	}

	free(env_var);
	return (1);
}
int _unsetenv(const char *name, shell_type *shell_info)
{
	unsigned int index = _getenv_index(name, shell_info);

	delete_node_at_index(&shell_info->env, index);
	return (index);
}

int main(void)
{
	shell_type shell_info;
	char *env_name = "PATH";
	char *value;

	initialize_custom_environ(&shell_info);
	value = _getenv(env_name, &shell_info);

	if (value != NULL)
	{
		printf("Value of %s: %s\n", env_name, value);
		free(value);
	}
	else
	{
		printf("%s not found in environment variables.\n", env_name);
	}

	printf("\nAll environment variables:\n");

	print_env(shell_info.env);
	_unsetenv("SHELL", &shell_info);
	print_env(shell_info.env);

	free_env(&shell_info.env);

	return (0);
}
