#ifndef SHELL_H
#define SHELL_H

/*std libs*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h> /* for open files*/
#include <errno.h>
#include <limits.h>
#include "macros.h"

/*
enum node_print_type
{
	ENV,
} ;
*/

typedef struct string_list_class
{
	int _num;
	char *_string;
	struct string_list_class *next;

} string_list_type;

/* shell program data structure */
typedef struct shell_class
{

	char **_tokens;
	int _token_count;
	char *_input_args;

	char *_buffer_read;
	char *_cmd;

	char *_path;
	char *_file_name;
	unsigned int _read_count;
	string_list_type *_aliases;
	string_list_type *_envs;
	string_list_type *_history;
	int _history_count;

	int _exec_count;
	int _file_descriptor;
	int _status;
	char **_env;

	int _env_changed;
	int _error_num;
	char **_cmd_chain;
	int _chain_stream_type;

} shell_type;

/* built in cmds program structure */
typedef struct builtins_class
{
	char *_cmd;
	int (*_fn)(shell_type *);
} builtins_type;

/*READ FUNCTIONS*/
int _read_file(char *file_name, char *buffer, ssize_t *file_size);

/* STRING UTILITIES FUNCTIONS */
int _strchr(const char *str, int c);
char *_strchr_ptr(char *str, int c);
char *_strtok(char *str, char *delimiters);
int str_len(char *str);
char *_strdupl(char *str);
void _reverse_str(char *str);
char *_strconcat(char dest[], char source[]);
int _strcmpr(char *str1, char *str2, int size);
int _isdigit(char ch);
char *_strcpy(char *destination, char *source);
char *_match_str_path(char *strs, char *str);
int _swap_string(char **old, char *new);
char *_convert_number(long int num, int base, int flags);

/*ALIAS FUNCTIONS */
int _patch_alias(shell_type *obj);

/* NODE FUNCTIONS */
void *_set_memory(char *ptr, char c, unsigned int size);
string_list_type *_append_node(string_list_type **head, char *str, int num);
string_list_type *_prepend_node(string_list_type **head, char *str, int num);
int _remove_node_at(string_list_type **head, unsigned int position);
char **_node_to_stringlist(string_list_type *head);
ssize_t _get_node_index(string_list_type *head, string_list_type *node);
size_t _node_length(string_list_type *head);
string_list_type *_match_node_str(string_list_type *node,
								  char *key, char c);

/* ENV UTILITIES FUNCTIONS */
int _match_env(char *envs_path, char *env_new);
int _unset_env(shell_type *obj, char *var);
int _set_env(shell_type *obj, char *var, char *var_value);
char **_get_envs(shell_type *obj);

/* ENV FUNCTIONS */
int _init_sys_envs(shell_type *obj, char *env[]);
int _shell_setenv(shell_type *obj);
int _shell_env(shell_type *obj);
int _shell_unsetenv(shell_type *obj);
char *_shell_getenv(shell_type *obj, char *name);

/* ERROR FUNCTIONS*/
int _args_errors(shell_type *obj, char *cmd_type);

/*SHELL UTILITIES*/
void _destroy_sh_obj(shell_type *obj, int total);
int _shell_refresh(shell_type *obj);
int _is_linked_stream(shell_type *obj, char *buffer, size_t *chain_pos);
void _create_shell_token(shell_type *obj);
char **_tokenize(char *str, char *deli);
void _set_shell_obj(shell_type *obj, char *argv[]);
int _swap_tokens(shell_type *obj);

void _next_linkedstream(shell_type *obj, char *buffer,
						size_t length, size_t index, size_t *position);

/* BUILTINS UTILITY FUNCTIONS*/
int _atoi(char *str);

/* BUILTINS FUNCTIONS */
int _shell_exit(shell_type *obj);
int _shell_cd(shell_type *obj);
int _shell_help(shell_type *obj);
int _shell_history(shell_type *obj);

/* WRITE FUNCTIONS*/
int _buffer_flush(char next_char, int buffer_index, char buffer[]);
int _write_char_to_stderr(char next_char, UNUSED int file_descriptor);
int _write_char_to_fd(char next_char, int file_descriptor);
int (*which_buffer(int fd))(char c, int fd);
int _write_char_to_stdeout(char next_char, UNUSED int file_descriptor);
int _write_string(char *str, int file_descriptor);
void _buffer_remove_comment(char *buffer);

/* PRINTS FUNCTIONS */
void _print_file_error(char *argv[]);
size_t _print_node_strlist(string_list_type *head);
void _print_error_msg(shell_type *obj, char *error_msg);
int _print_decimal(int num, int file_descriptor);

/* PRINT UTILITIES */
int _count_digits(int num);

/*MEMORY UTILITIES*/
int is_dynamic_mem(char *str);
void _free_strlistnode(string_list_type *node);
void _free_string_list(char **str_list);
void _free(char *str);
int _free_str_in_str(void **str);

/*HISTORY UTILITIES*/
void _history_size_monitor(shell_type *obj);

/*HISTORY FUNCTIONS*/
int _build_history(shell_type *obj, char *buffer, int line_count);
char *_get_history_file(shell_type *obj);
int _history_indexing(shell_type *obj);
int _write_history(shell_type *obj);
int _read_history(shell_type *obj);

#endif
