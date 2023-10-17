#include "shell.h"

/**
 * cmd_exit - Exits the shell with a specified status.
 * @info: Pointer to a struct containing potential arguments.
 * Return: -2 if shell should exit, 1 on error, 0 otherwise.
 */
int cmd_exit(info_t *info)
{
	int exit_status;

	if (info->argv[1])
	{
		exit_status = error_atoi(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			display_error(info, "Illegal number: ");
			error_puts(info->argv[1]);
			error_putchar('\n');
			return (1);
		}
		info->err_num = exit_status;
	}
	else
	{
		info->err_num = 0;
	}

	return (-2);
}

/**
 * cmd_cd - Changes the current directory of the process.
 * @info: Pointer to a struct containing potential arguments.
 * Return: 1 on error, 0 otherwise.
 */
int cmd_cd(info_t *info)
{
	char *dir, buffer[1024];
	int chdir_status;

	if (!info->argv[1])
	{
		dir = retrieve_env(info, "HOME=");
		chdir_status = (dir) ? chdir(dir) : chdir("/");
	}
	else if (string_compare(info->argv[1], "-") == 0)
	{
		dir = retrieve_env(info, "OLDPWD=");
		if (dir)
		{
			string_puts(dir);
			string_putchar('\n');
		}
		chdir_status = (dir) ? chdir(dir) : chdir("/");
	}
	else
	{
		chdir_status = chdir(info->argv[1]);
	}

	if (chdir_status == -1)
	{
		display_error(info, "can't cd to ");
		error_puts(info->argv[1]);
		error_putchar('\n');
		return (1);
	}
	else
	{
		add_env(info, "OLDPWD", retrieve_env(info, "PWD="));
		add_env(info, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}

/**
 * cmd_help - Displays help information for shell commands.
 * @info: Pointer to a struct containing potential arguments.
 * Return: Always 0.
 */
int cmd_help(info_t *info)
{
	(void)info;
	string_puts("Help function works. Implementation pending.\n");

	return (0);
}
