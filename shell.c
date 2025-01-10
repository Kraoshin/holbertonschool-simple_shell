#include "shell.h"

/**
 * main - choose between interactive or no-interactive mod for the shell
 *
 * Return: always 0
 */

int main(void)
{
	int status = 1;
	char **args, *line = NULL;

	while (status)
	{
		if (isatty(STDIN_FILENO))
			printf("simple_shell $ ");
		line = read_line();
		args = parse_line(line);
		status = exe_args(args);

		free(args);
		free(line);
	}

	return (EXIT_SUCCESS);
}
