#include "shell.h"

/**
 * shell_interactive - program that display simple_shell$ in loop until
 * and read parse execute differents args until you leave the shell
 */

void shell_interactive(void)
{
	char **args, *line;
	int status = -1;

	do {
		printf("simple_shell$");

		line = read_line();
		args = parse_line(line);
		status = exe_args(args);

		free(line);
		free(args);

	} while (status);
}
