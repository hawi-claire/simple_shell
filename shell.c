#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
/**
 * main - program runs the shell
 * @argc: number of arguments
 * @argv: an array of arguments
 * @env: pointer to an array of env variables
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv, char **env)
{

	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *argv_exec[2];
	char **environ = env;

	(void)argc;
	(void)argv;


	while (1)
	{
		write(STDOUT_FILENO, "simple_shell$ ", 14);
		fflush(stdout);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[nread - 1] == '\n')
		{
			line[nread - 1] = '\0';
		}
		argv_exec[0] = line;
		argv_exec[1] = NULL;

		if (execve(argv_exec[0], argv_exec, environ) == -1)
		{
			perror("execve");
		}

		free(line);
		line = NULL;
	}

	return (0);
}
