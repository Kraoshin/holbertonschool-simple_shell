#include "shell.h"

/**
 *
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

		if (status >= 0)
			exit(status);

	} while (status == -1);
}
