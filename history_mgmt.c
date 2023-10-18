#include "shell.h"

/**
* locate_history_file - determines the history file's location.
* @info: pointer to the parameter structure.
* Return: allocated string containing history file path or NULL on failure.
*/
char *locate_history_file(info_t *info)
{
char *buf, *dir;

dir = _getenv(info, "HOME=");
if (!dir)
return (NULL);

buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
if (!buf)
return (NULL);

buf[0] = 0;
_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HIST_FILE);

return (buf);
}

/**
* save_history - saves command history to a file.
* @info: pointer to the parameter structure.
* Return: 1 on success, -1 on failure.
*/
int save_history(info_t *info)
{
ssize_t fd;
char *filename = locate_history_file(info);
list_t *node;

if (!filename)
return (-1);

fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);

for (node = info->history; node; node = node->next)
{
_putsfd(node->str, fd);
_putfd('\n', fd);
}
_putfd(BUF_FLUSH, fd);
close(fd);

return (1);
}

/**
* load_history - retrieves command history from a file.
* @info: pointer to the parameter structure.
* Return: histcount on success, 0 on failure.
*/
int load_history(info_t *info)
{
int i, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf, *filename = locate_history_file(info);

if (!filename)
return (0);

fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
compile_history_list(info, buf + last, linecount++);
last = i + 1;
}
if (last != i)
compile_history_list(info, buf + last, linecount++);
free(buf);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
delete_node_at_index(&(info->history), 0);
reorder_history(info);
return (info->histcount);
}

/**
* compile_history_list - compiles the history into a linked list.
* @info: pointer to the parameter structure.
* @buf: buffer containing history command.
* @linecount: current line count in history.
* Return: Always 0.
*/
int compile_history_list(info_t *info, char *buf, int linecount)
{
list_t *node;

if (info->history)
node = info->history;

add_node_end(&node, buf, linecount);

if (!info->history)
info->history = node;

return (0);
}

/**
* reorder_history - renumbers the history list.
* @info: pointer to the parameter structure.
* Return: the updated histcount.
*/
int reorder_history(info_t *info)
{
list_t *node = info->history;
int i = 0;

while (node)
{
node->num = i++;
node = node->next;
}

return (info->histcount = i);
}
