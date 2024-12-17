#include "shell.c"

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

char **parse_line(char *line)
{
	int buffsize = 64, position = 0;
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

		if (i > buffsize)
		{
			fprintf(stderr, "Too many tokens, buffer size exceeded\n");
			break;
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
}
