#include "shell.h"

/**
 * cmd_history - Displays the history list, one command per line.
 * @info: Pointer to a struct containing potential arguments.
 * Return: Always 0.
 */
int cmd_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Removes an alias definition.
 * @info: Pointer to a struct containing potential arguments.
 * @str: The string representing the alias.
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *delimiter;
	int ret;

	delimiter = string_find_char(str, '=');
	if (!delimiter)
		return (1);
	*delimiter = '\0';
	ret = delete_node_by_key(&(info->alias), str);
	*delimiter = '=';
	return (ret);
}

/**
 * set_alias - Defines a new alias.
 * @info: Pointer to a struct containing potential arguments.
 * @str: The string representing the alias.
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *delimiter;

	delimiter = string_find_char(str, '=');
	if (!delimiter)
		return (1);
	if (!*(++delimiter))
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Displays a defined alias.
 * @node: Pointer to the alias node.
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *delimiter;

	if (node)
	{
		delimiter = string_find_char(node->str, '=');
		for (char *ptr = node->str; ptr <= delimiter; ptr++)
			string_putchar(*ptr);
		string_puts("='");
		string_puts(delimiter + 1);
		string_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * cmd_alias - Implements the alias builtin command.
 * @info: Pointer to a struct containing potential arguments.
 * Return: Always 0.
 */
int cmd_alias(info_t *info)
{
	char *delimiter;
	list_t *node;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (int i = 1; info->argv[i]; i++)
	{
		delimiter = string_find_char(info->argv[i], '=');
		if (delimiter)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
