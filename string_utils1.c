#include "shell.h"

/**
* string_copy - Copies a string from source to destination.
* @dest: Destination string.
* @src: Source string.
*
* Return: Pointer to the destination string.
*/
char *string_copy(char *dest, char *src)
{
int index = 0;

if (dest == src || !src)
return (dest);

while (src[index])
{
dest[index] = src[index];
index++;
}
dest[index] = '\0';

return (dest);
}

/**
* string_duplicate - Duplicates a string.
* @str: The string to duplicate.
*
* Return: Pointer to the duplicated string or NULL if failed.
*/
char *string_duplicate(const char *str)
{
int length = 0;
char *dup_str;

if (!str)
return (NULL);

while (str[length])
length++;

dup_str = malloc(sizeof(char) * (length + 1));
if (!dup_str)
return (NULL);

while (length >= 0)
{
dup_str[length] = str[length];
length--;
}

return (dup_str);
}

/**
* string_puts - Prints an input string.
* @str: The string to print.
*
* Return: Nothing.
*/
void string_puts(char *str)
{
if (!str)
return;

while (*str)
{
string_putchar(*str);
str++;
}
}

/**
* string_putchar - Writes the character to stdout.
* @c: The character to print.
*
* Return: On success 1. On error, -1 and sets errno appropriately.
*/
int string_putchar(char c)
{
static int index;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
{
write(1, buf, index);
index = 0;
}
if (c != BUF_FLUSH)
buf[index++] = c;

   return (1);
}
