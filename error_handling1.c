#include "shell.h"

/**
 * error_atoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in string, converted number otherwise. -1 on error.
 */
int error_atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (; s[i]; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result = (result * 10) + (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * display_error - Displays an error message.
 * @info: Pointer to the struct containing shell info.
 * @estr: String indicating the type of error.
 *
 * Return: void.
 */
void display_error(info_t *info, char *estr)
{
	error_puts(info->fname);
	error_puts(": ");
	print_digit(info->line_count, STDERR_FILENO);
	error_puts(": ");
	error_puts(info->argv[0]);
	error_puts(": ");
	error_puts(estr);
}

/**
 * print_digit - Prints an integer number.
 * @input: The number to print.
 * @fd: The file descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int print_digit(int input, int fd)
{
	int (*printer_func)(char) = putchar_fd;
	int count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		printer_func = error_putchar;

	_abs_ = (input < 0) ? -input : input;
	current = _abs_;

	for (int i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			printer_func('0' + current / i);
			count++;
		}
		current %= i;
	}
	printer_func('0' + current);
	count++;

	return (count);
}

/**
 * number_conversion - Converts a number to a string representation.
 * @num: The number to convert.
 * @base: The base to use for conversion.
 * @flags: Flags for conversion properties.
 *
 * Return: Pointer to the string representation of the number.
 */
char *number_conversion(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char *ptr;
	unsigned long n = (flags & CONVERT_UNSIGNED) ? (unsigned long) num :
		((num < 0) ? -num : num);

	array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
		*--ptr = '-';

	return (ptr);
}

/**
 * strip_comments - Removes comments (starting with '#') from a string.
 * @buf: Pointer to the string.
 *
 * Return: void.
 */
void strip_comments(char *buf)
{
	for (int i = 0; buf[i]; i++)
	{
		if (buf[i] == '#' && (i == 0 || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
