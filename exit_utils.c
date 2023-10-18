#include "shell.h"

/**
 * string_ncopy - Copies n characters of a string.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 * Return: The copied string.
 */
char *string_ncopy(char *dest, char *src, int n)
{
	int i;
	char *initial = dest;

	for (i = 0; src[i] && i < n; i++)
		dest[i] = src[i];

	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return (initial);
}

/**
 * string_ncat - Concatenates n characters of two strings.
 * @dest: The target string.
 * @src: The source string to append.
 * @n: The number of characters to append.
 * Return: The concatenated string.
 */
char *string_ncat(char *dest, char *src, int n)
{
	int dest_len, i;

	for (dest_len = 0; dest[dest_len] != '\0'; dest_len++)
		;

	for (i = 0; src[i] && i < n; i++)
		dest[dest_len + i] = src[i];

	dest[dest_len + i] = '\0';

	return (dest);
}

/**
 * char_search - Locates a character in a string.
 * @s: The string to search within.
 * @c: The character to search for.
 * Return: A pointer to the first occurrence of the character or NULL.
 */
char *char_search(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}
