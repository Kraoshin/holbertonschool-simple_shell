#ifndef SHELL_H
#define SHELL_H

#define TOK_DELIM " \t\r\n\a"

#include <stdio.h>
#include <unistd.h>

void shell_interactive(void);
void shell_no_interactive(void);

#endif
