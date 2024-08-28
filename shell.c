#include "main.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

/**
* main - entry point to simple_shell program
* @argc: number of arguments
* @argv: an array of arguments
* @env: the environment
*
* Return: Always 0 (Success)
*/

int main(int argc, char *argv[], char *env[])
{
	char *line = NULL;
	char *command = NULL;
	char *path = NULL, **path_tokens = NULL, *path_copy = NULL;
	int path_length;
	pid_t pid;
	int status;
	int interactive = isatty(STDIN_FILENO);


	(void)argc;

	/* if (argc != 1) */
		/* exit(0); fix this */

	path = find_path(env);

	if (path)
	{
		path_length = _strlen(path) + 1;
		path_copy = malloc(path_length);

		if (!path_copy)
			return (1); /* fix this */

		_strcpy(path_copy, path);
		path_tokens = tokenize(path_copy, ":");
	}

	while(1)
	{
		if (interactive)
			write(STDOUT_FILENO, "$ ", 2);

		line = get_line(STDIN_FILENO);
		if (line == NULL)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		line[strcspn(line, "\n")] = '\0';

		if (strlen(line) == 0)
		{
			free(line);
			continue;
		}

		command = find_command_in_path(line, path_tokens);
		if (!command)
		{
			command = line;
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(line);
			continue;
		}

		if (pid == 0)
		{
			if (execve(command, argv, env) == -1)
			{
				perror(command);
				free(line);
				exit(EXIT_FAILURE);
			}
		}

		else
		{
			wait(&status);
			free(line);
		}
	}

	free(path_copy);
	if (path_tokens != NULL)
		free_grid(path_tokens);

	return(0);
}
