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
	char **environ = env;

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

		if (execve(line, NULL, environ) == -1)
		{
			perror("execve");
		}

		free(line);
	}

	return (0);
}
