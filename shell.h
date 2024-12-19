#ifndef SHELL_H
#define SHELL_H

#define TOK_DELIM " \t\r\n\a"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

void shell_interactive(void);
void shell_no_interactive(void);
char *read_line(void);
char *read_stream(void);
char **parse_line(char *line);
int exe_args(char **args);
void print_env(void);
char *_getenv(const char *env_var);
char *is_a_command(char *args);

#endif
