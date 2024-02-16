# simple shell 🐚 🐌

## Repository Description 

0x16. C - Simple Shell 🐌
This repository contains the files to simulate a basic Unix Shell with its respective commands. It uses the POSIX API to implement many of the same functionalities of the unix Shell.

The predominantly used function calls are read, write, open, execve, exit, fflush, fork, free, malloc, getline, isatty, perror, strtok, wait, and waitpid.

This simple shell is a Shell interface written in C programming language that gives to the user a prompt `$`, after it accepts, it executes a user inputted command in a separate process called child process.


### Features🔭:
* This program displays a prompt and waits that the user types a command. A command line always ends with a new line (when user push ENTER key).
* The prompt is displayed again each time a command has been executed.
* When the user enters exit, simple shell will end and returns the status 0.
* The user could stop the program using Ctrl+D (end of file).
* This program executes the most common shell commands as ls, grep, find, pwd, rm, cp, mv, exit, env, history, etc... with arguments.
* If an executable cannot be found, It prints an error message and displays the prompt again.
* This Shell supports commentaries using #,
* The simple Shell does NOT support wildcard characters such as ls *.dat in parameters (or commands).
* This shell does NOT support pipes |, shell logical operators as && or ||, neither commands separator ;.
* it support command history caching to ***.simple_shell_history*** file in user home directory.

## cloning, Compiling
To run this shell, clone this repository in your terminal.
* HTTPS 🌐
  ```
  $ git clone https://github.com/HucksApp/simple_shell.git
  ```
  * SSH 🐚
  ```
  $ git clone git@github.com:HucksApp/simple_shell.git
  ```
  * To compile
 ```
  $ gcc -Wall -Wextra -Werror -pedantic -Wno-format -g *.c -o simple_shell
```

## Usage

```
$ ./simple_shell
```

### builtin command🛠
This program executes the most common shell commands but the directly builtins are

***cd exit env setenv unset help***

command       |      Description
--------------|------------------
cd            |  cd <directory>   -- move to specified directory or home if no dir specified
env           | env  --  prints enviroment variables
setenv        | setenv <variable> <value> -- set enviroment variable new or existing
unset         | unset <variable>  -- unset enviroment variable new or existing
help          | help <command>  -- prints detail and usage of command

### example
```
$ help help

help:   help [BUILTIN_NAME]

        Display information about builtin commands.

        Displays brief summaries of builtin commands.  If BUILTIN_NAME is
        specified, gives detailed help on all commands matching BUILTIN_NAME,
        otherwise the list of help topics is printed BUILTIN_NAME list.
        Arguments:

        BUILTIN_NAME specifiying a help topic.

        cd      [dir]
        exit    [status]
        env
        setenv  [variable value]
        unset   [variable]
        help    [built_name]

$
```

### Author 🖋

Abiodun Aremu ~ HucksApp@gmail.com :




 
