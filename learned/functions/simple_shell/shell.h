#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct env_list
{
	char *str;
	struct env_list *next;
} env_t;

typedef struct shell_class
{
	env_t *env;
	char **environ;
} shell_type;

size_t print_env(const env_t *h);
char *_getenv(const char *name);
int _getenv_index(const char *name);
void initialize_custom_environ(shell_type *shell_info);

void free_env(env_t **head);
int delete_node_at_index(env_t **head, unsigned int index);
env_t *add_node_end(env_t **head, const char *str);
env_t *add_node(env_t **head, const char *str);
int _setenv(shell_type *shell_info, const char *name,
			const char *value, int overwrite);

#endif
