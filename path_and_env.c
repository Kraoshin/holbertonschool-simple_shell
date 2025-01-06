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
	int i = 0;
	char *key;

	while (env[i])
	{
		key = strtok(env[i], "=");
		if (strcmp(env_var, key) == 0)
			return (strtok(NULL, "\n"));
		i++;
	}
	return (NULL);
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
	char *env = _getenv("PATH"), *token, *tmp, *result;
	struct stat st;

	if (!env)
		return (NULL);
	if (access(args, X_OK) == 0)
		return (strdup(args));

	token = strtok(env, ":");

	while (token)
	{
		tmp = malloc(strlen(token) + strlen(args) + 2);

		if (!tmp)
		{
			perror("Allocation failed");
			return (NULL);
		}

		strcpy(tmp, token);
		strcat(tmp, "/");
		strcat(tmp, args);

		if (stat(tmp, &st) == 0)
		{
			result = strdup(tmp);
			free(tmp);
			return (result);
		}

		free(tmp);

		token = strtok(NULL, ":");
	}

	return (NULL);
}
