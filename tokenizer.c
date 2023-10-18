#include "shell.h"

/**
 * is_delim - helper function to check if a character is a delimiter.
 * @c: the character to check
 * @d: the delimiter string
 * Return: 1 if c is a delimiter, 0 otherwise
 */
static int is_delim(char c, const char *d)
{
	while (*d)
	{
		if (c == *d++)
			return (1);
	}
	return (0);
}

/**
 * string_to_words - Splits a string into words based on delimiter string.
 * @str: The input string.
 * @delim: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **string_to_words(char *str, char *delim)
{
	int i, j, k, m, numwords = 0;
	char **words;

	if (!str || !*str)
		return (NULL);

	delim = delim ? delim : " ";

	for (i = 0; str[i]; i++)
		if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || !str[i + 1]))
			numwords++;

	if (!numwords)
		return (NULL);

	words = malloc((numwords + 1) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], delim))
			i++;
		for (k = 0; !is_delim(str[i + k], delim) && str[i + k]; k++)
			;
		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			while (j)
				free(words[--j]);
			free(words);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			words[j][m] = str[i++];
		words[j][m] = '\0';
	}
	words[j] = NULL;

	return (words);
}

/**
 * string_to_array - Splits a string into words based on a delimiter character.
 * @str: The input string.
 * @delim: The delimiter character.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **string_to_array(char *str, char delim)
{
	int i, j, k, m, numwords = 0;
	char **array;

	if (!str || !*str)
		return (NULL);

	for (i = 0; str[i]; i++)
		if (str[i] != delim && (!str[i + 1] || str[i + 1] == delim))
			numwords++;

	if (!numwords)
		return (NULL);

	array = malloc((numwords + 1) * sizeof(char *));
	if (!array)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == delim)
			i++;
		for (k = 0; str[i + k] != delim && str[i + k]; k++)
			;
		array[j] = malloc((k + 1) * sizeof(char));
		if (!array[j])
		{
			while (j)
				free(array[--j]);
			free(array);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			array[j][m] = str[i++];
		array[j][m] = '\0';
	}
	array[j] = NULL;

	return (array);
}
