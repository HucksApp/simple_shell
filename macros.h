#ifndef MACROS_H
#define MACROS_H

/* Buffer size*/
#define BUFFER_SIZE 1024

/* signal to output all of buffer to stream */
#define BUFFER_FLUSH -1

/* Cast for unused variable or arguments */
#define UNUSED __attribute__((unused))

#define ERROR_MESSAGES \
	((char const *[]){"Illegal number: ", "can't cd to "})

/* PROMPT CHARACTER */
#define PROMPT "$ "

/*Boolean value FALSE */
#define _FALSE 0

/*Boolean value TRUE */
#define _TRUE 1

/* null terminator */
#define null '\0'

#define HISTORY_FILE ".simple_shell_history"

/**/
#define HISTORY_SIZE (5 * BUFFER_SIZE)

/* convert switch */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define CMD_NUL 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Errors -> command or file not found */
#define FILE_NOT_FOUND 127

/* Errors -> permission denied */
#define PERMISSION_DENIED 126

/* Errors -> OS system function error */
#define SYS_ERROR -1
#define EXIT_SIG -2

#define MAX_ALIAS 10

/************* FORMATTED STRING FOR HELP BUILT IN **************/

#define HELP_CD_MSG "cd=\n"                                                               \
					"cd:\tcd [dir]\n\n"                                                   \
					"	Change the shell working directory.\n\n"                            \
					"	If no argument is given to cd the command will be interpreted\n"    \
					"	as cd $HOME.\n"                                                     \
					"	if the argumenthelp is - (cd -), the command will be interpreted\n" \
					"	as cd $OLDPWD.\n\n"

#define HELP_EXIT_MSG "exit=\n"                                                                  \
					  "exit:\texit [STATUS]\n\n"                                                 \
					  "	Exit of the simple-shell.\n\n"                                           \
					  "	Exits the shell with a status of N.  If N is omitted, the exit status\n" \
					  "	is that of the last command executed.\n\n"

#define HELP_ENV_MSG "env=\n"                  \
					 "env:\tenv \n\n"          \
					 "	Print environment.\n\n" \
					 "	The env command will be print a complete list of enviroment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"                                                           \
						"setenv:\tsetenv VARIABLE VALUE\n\n"                                  \
						"	Change or add an environment variable.\n\n"                         \
						"	initialize a new environment variable, or modify an existing one\n" \
						"	When there are not correct numbers of arguments print error message.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"                                                           \
						  "unsetenv:\tunsetenv VARIABLE\n\n"                                      \
						  "	The unsetenv function deletes one variable from the environment.\n\n" \
						  "	When there are not correct numbers of arguments print error message.\n\n"

#define HELP_MSG "help=\n"                                                                  \
				 "help:\thelp [BUILTIN_NAME]\n\n"                                           \
				 "	Display information about builtin commands.\n\n"                         \
				 "	Displays brief summaries of builtin commands.  If BUILTIN_NAME is\n"     \
				 "	specified, gives detailed help on all commands matching BUILTIN_NAME,\n" \
				 "	otherwise the list of help topics is printed BUILTIN_NAME list.\n"       \
				 "	Arguments:\n\n"                                                          \
				 "	BUILTIN_NAME specifiying a help topic.\n\n"                              \
				 "	cd\t[dir]\n"                                                             \
				 "	exit\t[status]\n"                                                        \
				 "	env\n"                                                                   \
				 "	setenv\t[variable value]\n"                                              \
				 "	unset\t[variable]\n"                                                     \
				 "	help\t[built_name]\n\n"

#endif
