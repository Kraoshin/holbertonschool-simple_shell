#include "shell.h"

/**
 *
 */

int main(void)
{
	if (isatty(STDIN_FILENO) == 1)
		shell_interactive();

	else
		shell_no_interractive();

	return (0);
}
