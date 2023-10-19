#include "shell.h"

/**
* main - Entry point for the shell program.
* @ac: Argument count.
* @av: Argument vector.
*
* Return: 0 on success, 1 on error.
*/
int main(int ac, char **av)
{
/* Initialize the info structure with default values */
info_t info[] = { INFO_INIT};

/* Set the standard file descriptor for error messages */
int fd = STDERR_FILENO; /* STDERR_FILENO is typically 2 */

/* If there are exactly 2 arguments, attempt to open a file */
if (ac == 2)
{
fd = open(av[1], O_RDONLY);

if (fd == -1)
{
if (errno == EACCES)
{
exit(126); /* Error code 126 for permission denied */
}
else if (errno == ENOENT)
{
fprintf(stderr, "%s: 0: Can't open %s\n", av[0], av[1]);
exit(127); /* Error code 127 for file not found */
}
return (EXIT_FAILURE);
}

/* Update the info structure with the opened file descriptor */
info->readfd = fd;
}

/* Populate the environment list */
populate_env_list(info);

/* Read history (assume this is a function from your shell) */
read_history(info);

/* Execute the shell (assuming hsh is the shell's main function) */
hsh(info, av);

return (EXIT_SUCCESS);
}
