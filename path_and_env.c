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
	char *env = _getenv("PATH"), *token, *tmp, *path;
	struct stat st;

	if (!env)
		return (NULL);

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
			if (access(tmp, X_OK) == 0)
			{
				path = strdup(tmp);

				free(tmp);

				return (path);
			}
		}

		free(tmp);

		token = strtok(NULL, ":");
	}

	return (NULL);
}
