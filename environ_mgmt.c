#include "shell.h"

/**
 * cmd_env - Displays the current environment.
 * @info: Pointer to the structure containing potential arguments.
 * Return: Always 0.
 */
int cmd_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * retrieve_env - Fetches the value of an environment variable.
 * @info: Pointer to the structure containing potential arguments.
 * @name: Name of the environment variable.
 * Return: Value of the environment variable or NULL if not found.
 */
char *retrieve_env(info_t *info, const char *name)
{
	list_t *node = info->env;

	while (node)
	{
		char *value = starts_with(node->str, name);

		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * cmd_setenv - Initializes or modifies an environment variable.
 * @info: Pointer to the structure containing potential arguments.
 * Return: 0 on success, 1 on failure.
 */
int cmd_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		string_puts("Incorrect number of arguments\n");
		return (1);
	}
	return (_setenv(info, info->argv[1], info->argv[2]) ? 0 : 1);
}

/**
 * cmd_unsetenv - Removes an environment variable.
 * @info: Pointer to the structure containing potential arguments.
 * Return: 0 on success, 1 on failure.
 */
int cmd_unsetenv(info_t *info)
{
	if (info->argc == 1)
	{
		string_puts("Too few arguments.\n");
		return (1);
	}
	for (int i = 1; i < info->argc; i++)
	{
		_unsetenv(info, info->argv[i]);
	}
	return (0);
}

/**
 * set_env_list - Populates the envir linked list from the global environ.
 * @info: Pointer to the structure containing potential arguments.
 * Return: Always 0.
 */
int set_env_list(info_t *info)
{
	for (size_t i = 0; environ[i]; i++)
	{
		add_node_end(&(info->env), environ[i], 0);
	}
	return (0);
}
