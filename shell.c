#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
extern char **environ;

/**
 * main - entry point
 *
 * Return: 0 on success
 */
int main(void)
{
    pid_t pid;
    char input[MAX_INPUT];
    char *args[2];
    int status;

    args[1] = NULL;

    while (1)
    {
        printf("#cisfun$ ");
        fflush(stdout);

        /* Read user input */
        if (fgets(input, MAX_INPUT, stdin) == NULL)
        {
            break;
        }

        /* Remove newline character from input */
        input[strlen(input) - 1] = '\0';

        /* Fork a new process */
        pid = fork();

        if (pid < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            /* Child process */
            args[0] = input;
            execve(args[0], args, environ);
            perror(input);
            exit(1);
        }
        else
        {
            /* Parent process */
            if (waitpid(pid, &status, 0) == -1)
            {
                perror("waitpid");
                exit(1);
            }
        }
    }

    printf("\n");
    return (0);
}
