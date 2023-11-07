#ifndef SHELL_H
#define SHELL_H

typedef struct env_list
{
	char *str;
	struct env_list *next;
} env_t;

typedef struct shell_class
{
	char **_env;
} shell_type;

#endif
