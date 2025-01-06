#include "shell.h"

/**
 * read_line - read line input using getline function
 *
 * Return: The buffer containing the line read by getline
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
		fprintf(stderr, "memory allocation failed\n");

	token = strtok(line, TOK_DELIM);

	while (token)
	{

		if (position >= buffsize)
		{
			fprintf(stderr, "Too many tokens, buffer size exceeded\n");
			exit(EXIT_FAILURE);
		}

		tokens[position] = strdup(token);
		position++;

		token = strtok(NULL, TOK_DELIM);
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

int exe_args(char **args)
{
	pid_t pid;
	int status;
	char *path;

	if (!args[0])
		return (1);

	if (strcmp(args[0], "exit") == 0)
		return (0);
	else if (strcmp(args[0], "env") == 0)
		print_env();

	else
	{
		path = is_a_command(args[0]);

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

		if (path)
			free(path);
	}
	return (1);
}