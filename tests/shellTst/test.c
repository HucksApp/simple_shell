#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void execute_command(char* command) {
    // Split the command into tokens
    char* tokens[10];  // Assuming a maximum of 10 tokens
    int token_count = 0;
    char* token = strtok(command, " \t\n");
    while (token != NULL) {
        tokens[token_count] = token;
        token_count++;
        token = strtok(NULL, " \t\n");
    }
    tokens[token_count] = NULL;  // Null-terminate the array of tokens

    // Create a new process to run the command
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(tokens[0], tokens) == -1) {
            perror("shell");
        }
        exit(1);
    } else if (pid < 0) {
        perror("shell");
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        printf("myShell> ");
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
        printf("here");
            break;
        }

        // Remove the newline character
        input[strlen(input) - 1] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        }

        execute_command(input);
    }

    return 0;
}




