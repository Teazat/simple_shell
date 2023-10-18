#include "shell.h"

/**
* main_hsh_loop - Entry point function for the shell program.
* @av: Argument vector.
*
* Return: 0 on success, 1 on error.
*/
int main_hsh_loop(char **av)
{
info_t info = INFO_DEFAULT;
int fd = 2;

/* Removed inline assembly for better portability and clarity */
fd += 3;

if (av && av[1])
{
fd = open(av[1], O_RDONLY);
if (fd == -1)
{
perror(av[1]);
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
_eputs(av[0]);
_eputs(": 0: Can't open ");
_eputs(av[1]);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
info.read_fd = fd;
}
populate_env_list(&info);
read_history(&info);
hsh_loop(&info, av);
return (EXIT_SUCCESS);
}
