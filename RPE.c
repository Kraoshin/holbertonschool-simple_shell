#include "shell.h"

/**
 * read_line - read line input using getline function and handle eof
 *
 * Return: The buffer containing the line read by getline
 */

char *read_line(void)
{
	char *line = NULL;
	size_t buffsize = 0;
	ssize_t bread;

	bread = getline(&line, &buffsize, stdin);
	if (bread == -1)
	{
		free(line);
		/* ADDED: Newline for EOF in interactive mode */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		exit(EXIT_SUCCESS);
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
	char **tokens = malloc(buffsize * sizeof(char *));
	/* ADDED: Token copy variable */
	char *token, *token_copy;

	if (!tokens)
	{
		/* CHANGED: Error message from "allocation error" to "hsh" */
		perror("hsh");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");
	while (token)
	{
		/* CHANGED: Better buffer overflow protection*/
		if (position >= buffsize - 1)
			break;


		/*ADDED: Create copy of token to prevent memory issues*/
		token_copy = strdup(token);
		if (!token_copy)
		{
			perror("hsh");
			exit(EXIT_FAILURE);
		}

		/* CHANGED: Store copy instead of direct token */
		tokens[position++] = token_copy;
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

int exe_args(char **args)
{
	pid_t pid;
	int status;
	char *path;

	if (!args[0])
		return (1);

	if (strcmp(args[0], "exit") == 0)
		return (0);


	/* ADDED: env builtin command */
	if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	path = is_a_command(args[0]);

	if (!path)
	{
		/* CHANGED: Error message format to match requirements */
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		return (127);
	}

	pid = fork();

	if (pid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			/* CHANGED: Error message prefix*/
			perror("./hsh");
			/* ADDED: Free path before exit*/
			free(path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0i)
	{
		perror("./hsh");
		/* ADDED: Free path on errot */
		free(path);
		return (1);
	}

	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}


	free(path);
	/* CHANGED: Return actual exit status */
	return (WEXITSTATUS(status));
}
