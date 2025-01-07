#include "shell.h"

/**
 * print_env - print the current environment
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
 * _getenv - compare the value stocked in env_var with a key of the environment
 *
 * @env_var: contains a string to compare with a key (what's before = in the
 * environment)
 *
 * Return: NULL no equivalence, the key=value tokenized
 */

char *_getenv(const char *env_var)
{
	char **env = environ;
	size_t len = strlen(env_var);

	while (*env)
	{
		if (strncmp(*env, env_var, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);
		env++;
	}
	return (0);
}

/**
 * is_a_command - check if the input is a command using _getenv
 * and access function
 *
 * @args: the input tokenized
 *
 * Return: NULL if anything fail during the process, otherwise the path of
 * the command to execute
 */

char *is_a_command(char *args)
{
	char *path, *tmp, *dir, *result;
	struct stat st;

	if (access(args, X_OK) == 0)
		return (strdup(args));

	path = _getenv("PATH");
	if (!path)
		return (NULL);

	tmp = strdup(path);
	if (!tmp)
		return (NULL);

	result = malloc(4096);
	if (!result)
	{
		free(tmp);
		return (NULL);
	}

	dir = strtok(tmp, ":");
	while (dir)
	{
		sprintf(result, "%s/%s", dir, args);

		if (stat(result, &st) == 0 && access(result, X_OK) == 0)
		{
			free(tmp);
			return (result);
		}
		dir = strtok(NULL, ":");
	}

	free(result);
	free(tmp);
	return (NULL);
}
