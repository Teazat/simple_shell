#include "shell.h"

/**
* string_length - returns the length of a string
* @s: the string to evaluate
*
* Return: integer length of the string
*/
int string_length(char *s)
{
int length = 0;

if (!s)
return (0);

while (*s++)
length++;

return (length);
}

/**
* string_compare - Compares two strings lexicographically.
* @s1: the first string
* @s2: the second string
*
* Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/
int string_compare(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
return (*s1 - *s2);
}

/**
* string_starts_with - Checks if a string starts with a given substring.
* @haystack: the main string
* @needle: the substring to check
*
* Return: address of the next character in haystack after needle or NULL
*/
char *string_starts_with(const char *haystack, const char *needle)
{
while (*needle)
{
if (*needle++ != *haystack++)
return (NULL);
}
return ((char *)haystack);
}

/**
* string_concat - Concatenates two strings.
* @dest: destination string
* @src: source string
*
* Return: pointer to the concatenated string
*/
char *string_concat(char *dest, char *src)
{
char *start = dest;

while (*dest)
dest++;

while (*src)
*dest++ = *src++;

*dest = '\0';
return (start);
}
