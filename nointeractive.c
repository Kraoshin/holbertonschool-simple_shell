#include "shell.h"

/**
 *
 */

void shell_no_interactive(void)
{
	char **args, *line;
	int status = -1;

	do {
		line = read_line();
		args = parse_line(line);
		status = exe_args(args);

		free(line);
		free(args);

	} while (status);
}
