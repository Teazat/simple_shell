#include "shell.h"

/**
* reset_info - resets fields in the info_t struct
* @info: pointer to info_t struct
*/
void reset_info(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}

/**
* initialize_info - initializes fields in the info_t struct
* @info: pointer to info_t struct
* @av: argument vector
*/
void initialize_info(info_t *info, char **av)
{
int i = 0;

info->fname = av[0];
if (info->arg)
{
info->argv = strtow(info->arg, " \t");
if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);
if (info->argv)
{
info->argv[0] = _strdup(info->arg);
info->argv[1] = NULL;
}
}
for (i = 0; info->argv && info->argv[i]; i++)
;
info->argc = i;

replace_alias(info);
replace_vars(info);
}
}

/**
* release_info - releases memory used by fields in the info_t struct
* @info: pointer to info_t struct
* @all: flag to indicate if all fields should be freed
*/
void release_info(info_t *info, int all)
{
ffree(info->argv);
info->argv = NULL;
info->path = NULL;

if (all)
{
if (!info->cmd_buf)
free(info->arg);
if (info->env)
free_list(&(info->env));
if (info->history)
free_list(&(info->history));
if (info->alias)
free_list(&(info->alias));
ffree(info->environ);
info->environ = NULL;
bfree((void **)info->cmd_buf);
if (info->readfd > 2)
close(info->readfd);
__putchar(BUF_FLUSH);
}
}
