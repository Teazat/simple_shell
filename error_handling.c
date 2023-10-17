#include "shell.h"

/**
 * error_puts - Prints a string to stderr.
 * @str: String to be printed.
 *
 * Return: void.
 */
void error_puts(char *str)
{
	if (!str)
		return;

	while (*str)
		error_putchar(*str++);
}

/**
 * error_putchar - Writes a character to stderr.
 * @c: Character to print.
 *
 * Return: 1 on success. On error, -1 is returned and errno is set.
 */
int error_putchar(char c)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(STDERR_FILENO, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;

	return (1);
}

/**
 * putchar_fd - Writes a character to a given file descriptor.
 * @c: Character to print.
 * @fd: File descriptor to write to.
 *
 * Return: 1 on success. On error, -1 is returned and errno is set.
 */
int putchar_fd(char c, int fd)
{
	static int index;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(fd, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;

	return (1);
}

/**
 * puts_fd - Prints a string to a specified file descriptor.
 * @str: String to be printed.
 * @fd: File descriptor to write to.
 *
 * Return: Number of characters written.
 */
int puts_fd(char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);

	while (*str)
		count += putchar_fd(*str++, fd);

	return (count);
}
