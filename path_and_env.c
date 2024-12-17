#include "shell.h"

/**
 *
 */

void print_env(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 *
 */

char *_getenv(const char *env_var)
{
	char **env = environ;
	size_t var_len = strlen(env_var);

	while (*env)
	{
		if (strncmp(*env, env_var, var_len) == 0 && (*env)[var_len] == '=')
			return (*env + var_len + 1);
		env++;
	}

	return (NULL);
}

/**
 *
 */

char *is_a_command(char *args)
{

