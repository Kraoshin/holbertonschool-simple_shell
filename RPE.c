#include "shell.h"

/**
 * read_line - read line input using getline function and handle eof
 *
 * Return: The buffer containing the line read by getline
 */

char *read_line(void)
{
	int i;
	char *line = NULL;
	size_t buffsize = 0;
	ssize_t bread = getline(&line, &buffsize, stdin);

	if (bread == EOF)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}

	if (bread == -1)
	{
		free(line);
		exit(EXIT_SUCCESS);
	}

	i = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break;
		}
		i++;
	}

	return (line);
}

/**
 * parse_line - tokenize the line received from read_line function
 *
 * @line: buffer containing line read by read_line function
 *
 * Return: the string tokenized
 */

char **parse_line(char *line)
{
	int buffsize = 100, position = 0;
	char **tokens = malloc(buffsize * sizeof(char *)), *token;

	if (!tokens)
	{
		perror("allocation error");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");

	while (token)
	{
		if (position < buffsize)
			tokens[position++] = token;
		else
			break;

		token = strtok(NULL, " \t\r\n\a");
	}

	tokens[position] = NULL;

	return (tokens);
}

/**
 * exe_args - take the tokenized string from parse_line function, check if
 * the input isnt some built-in function, then if a path exist through
 * is_a_command fonction then create a child process of the command input
 * if it exist
 *
 * @args: pointer to a pointer containing the tokenized string
 *
 * Return: 1 if there is any failure
 */

int exe_args(char **args, char *line)
{
	pid_t pid;
	int status;
	char *path;

	if (!args[0])
		return (0);
	if (strncmp(args[0], "exit", 4) == 0)
	{
		status = 0;
		if (args[1])
			status = atoi(args[1]);
		free(args);
		free(line);
		exit(status);
	}
	path = is_a_command(args[0]);

	if (!path)
	{
		fprintf(stderr, "hsh %s: command not found\n", args[0]);
		return (127);
	}
	pid = fork();

	if (pid == 0)
	{
		if (execve(path, args, environ) == -1)
			perror("hsh");
		_exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("hsh");
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(path);

	return (1);
}
