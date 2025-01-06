#include "shell.h"

/**
 * main - choose between interactive or no-interactive mod for the shell
 *
 * Return: always 0
 */

int main(void)
{
	if (isatty(STDIN_FILENO) == 1)
		shell_interactive();

	else
		shell_no_interactive();

	return (0);
}
