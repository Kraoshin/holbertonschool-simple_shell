#include "shell.h"

/**
 *
 */

char *read_line(void)
{
	char *line = NULL;
	size_t buffsize = 0;

	if (getline(&line, &buffsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		else
		{
			free(line);
			perror("error while reading the line from stdin");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}

/**
 *
 */

char *read_stream(void)
{
	int buffsize = 1024, position = 0;
	char *line = malloc(sizeof(char) * buffsize), charac;
	ssize_t bytes_read;

	if (!line)
	{
		fprintf(stderr, "allocation failed");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		bytes_read = read(STDIN_FILENO, &charac, 1);

		if (bytes_read == -1)
		{
			perror("read");
			free(line);
			exit(EXIT_FAILURE);
		}

		else if (bytes_read == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		else if (charac == '\n')
		{
			line[position] = '\0';
			return (line);
		}

		else
			line[position] = charac;

		position++;
	}
}

/**
 *
 */

char **parse_line(char *line)
{
	int buffsize = 100, position = 0;
	char **tokens = malloc(buffsize * sizeof(char *)), *token;

	if (!tokens)
	{
		fprintf(stderr, "memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOK_DELIM);

	while (token)
	{
		tokens[position] = token;
		position++;

		if (position >= buffsize)
		{
			fprintf(stderr, "Too many tokens, buffer size exceeded\n");
			exit(EXIT_FAILURE);
		}

		token = strtok(NULL, TOK_DELIM);
	}

	tokens[position] = NULL;

	return (tokens);
}

/**
 *
 */

int exe_args(char **args)
{
	pid_t pid;
	int status;
	char *path;

	if (args[0] == NULL)
		return (1);

	if (strcmp(args[0], "exit") == 0)
		return (0);

	path = is_a_command(args[0]);

	if (!path)
	{
		fprintf(stderr, "%s command unknown\n", args[0]);
		return (2);
	}

	pid = fork();

	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("Error during child process");
		exit(EXIT_FAILURE);
	}

	else if (pid < 0)
		perror("Forking error");

	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	free(path);

	return (1);
}
